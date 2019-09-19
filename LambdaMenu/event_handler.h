#include <msgpack.hpp>

// function traits
// see https://github.com/rpclib/rpclib/blob/ec7ecbe3ff8057f686a51ceffdf2fb74e13c3723/LICENSE.md for license terms
namespace detail
{
	template<typename T>
	using invoke = typename T::type;

	template<typename T, T I>
	struct constant : std::integral_constant<T, I> {};

	template<bool B>
	using bool_ = constant<bool, B>;

	using true_ = bool_<true>;

	using false_ = bool_<false>;

	template <int N>
	using is_zero = invoke<std::conditional<(N == 0), true_, false_>>;

	template <int N, typename... Ts>
	using nth_type = invoke<std::tuple_element<N, std::tuple<Ts...>>>;

	namespace tags {

		// tags for the function traits, used for tag dispatching
		struct zero_arg {};
		struct nonzero_arg {};
		struct void_result {};
		struct nonvoid_result {};

		template <int N> struct arg_count_trait { typedef nonzero_arg type; };

		template <> struct arg_count_trait<0> { typedef zero_arg type; };

		template <typename T> struct result_trait { typedef nonvoid_result type; };

		template <> struct result_trait<void> { typedef void_result type; };
	}

	//! \brief Provides a small function traits implementation that
	//! works with a reasonably large set of functors.
	template <typename T>
	struct func_traits : func_traits<decltype(&T::operator())> {};

	template <typename C, typename R, typename... Args>
	struct func_traits<R(C::*)(Args...)> : func_traits<R(*)(Args...)> {};

	template <typename C, typename R, typename... Args>
	struct func_traits<R(C::*)(Args...) const> : func_traits<R(*)(Args...)> {};

	template <typename R, typename... Args> struct func_traits<R(*)(Args...)> {
		using result_type = R;
		using arg_count = std::integral_constant<std::size_t, sizeof...(Args)>;
		using args_type = std::tuple<typename std::decay<Args>::type...>;
	};

	template <typename T>
	struct func_kind_info : func_kind_info<decltype(&T::operator())> {};

	template <typename C, typename R, typename... Args>
	struct func_kind_info<R(C::*)(Args...)> : func_kind_info<R(*)(Args...)> {};

	template <typename C, typename R, typename... Args>
	struct func_kind_info<R(C::*)(Args...) const>
		: func_kind_info<R(*)(Args...)> {};

	template <typename R, typename... Args> struct func_kind_info<R(*)(Args...)> {
		typedef typename tags::arg_count_trait<sizeof...(Args)>::type args_kind;
		typedef typename tags::result_trait<R>::type result_kind;
	};

	template <typename F> using is_zero_arg = is_zero<func_traits<F>::arg_count>;

	template <typename F>
	using is_single_arg =
		invoke<std::conditional<func_traits<F>::arg_count == 1, true_, false_>>;

	template <typename F>
	using is_void_result = std::is_void<typename func_traits<F>::result_type>;

	//! \brief Calls a functor with argument provided directly
	template <typename Functor, typename Arg>
	auto call(Functor f, Arg &&arg)
		-> decltype(f(std::forward<Arg>(arg)))
	{
		return f(std::forward<Arg>(arg));
	}

	template <typename Functor, typename... Args, std::size_t... I>
	decltype(auto) call_helper(Functor func, std::tuple<Args...> &&params,
		std::index_sequence<I...>) {
		return func(std::get<I>(params)...);
	}

	//! \brief Calls a functor with arguments provided as a tuple
	template <typename Functor, typename... Args>
	decltype(auto) call(Functor f, std::tuple<Args...> &args) {
		return call_helper(f, std::forward<std::tuple<Args...>>(args),
			std::index_sequence_for<Args...>{});
	}
}
// end function traits

using TEventHandler = void(*)(void*, const char*, const void*, uint32_t);

#ifdef SERVER_SIDED
IMPORT void add_event_handler(const char* name, TEventHandler handler, void* context);
#else
void add_event_handler(const char* name, TEventHandler handler, void* context)
{

}
#endif

struct EventHandler
{
private:
	template<typename TFn>
	struct Context
	{
		TFn handler;

		Context(const TFn& handler)
			: handler(handler)
		{

		}

		using args_type = typename detail::func_traits<TFn>::args_type;

		static void Handle(void* cxt, const char* eventName, const void* data, uint32_t dataSize)
		{
			reinterpret_cast<Context*>(cxt)->HandleInternal(eventName, data, dataSize);
		}

		void HandleInternal(const char* eventName, const void* data, uint32_t dataSize)
		{
			auto objectHandle = msgpack::unpack(reinterpret_cast<const char*>(data), dataSize);
			auto object = objectHandle.get();

			args_type args;
			object.convert(args);

			detail::call(handler, args);
		}
	};

public:
	template<typename TFn>
	EventHandler(const std::string& name, const TFn& handler)
	{
		auto context = new Context<TFn>(handler);
		add_event_handler(name.c_str(), &Context<TFn>::Handle, context);
	}
};