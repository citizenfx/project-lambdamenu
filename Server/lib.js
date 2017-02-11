var library = {
	'$NATIVE': {
		callNative: function()
		{
			'use strict';

			let args = [ nativeState.hash ];
			let hadPointer = false;

			let pointerTypes = [];

			for (let arg of nativeState.arguments)
			{
				if (arg.type == 'ptr')
				{
					switch (arg.ptrType)
					{
						case 1:
						case 2:
							args.push(Citizen.pointerValueIntInitialized(getValue(arg.ptr, 'i32')));
							pointerTypes.push(arg);
							break;

						case 3:
							args.push(Citizen.pointerValueFloatInitialized(getValue(arg.ptr, 'float')));
							pointerTypes.push(arg);
							break;

						case 4:
							args.push(Citizen.pointerValueVector());
							pointerTypes.push(arg);
							break;
					}

					hadPointer = true;
				}
				else
				{
					args.push(arg.val);
				}
			}

			for (let arg of arguments)
			{
				args.push(arg);
			}

			args.push(Citizen.returnResultAnyway());

			let retval = Citizen.invokeNative.apply(this, args);

			if (!hadPointer)
			{
				return retval;
			}

			let singleValue = retval.shift();

			for (let i = 0; i < pointerTypes.length; i++)
			{
				let val = retval[i];
				let pt = pointerTypes[i];

				if (pt.ptrType == 4)
				{
					setValue(pt.ptr, val[0], 'float');
					setValue(pt.ptr + 8, val[1], 'float');
					setValue(pt.ptr + 16, val[2], 'float');
				}
				else if (pt.ptrType == 1 || pt.ptrType == 2)
				{
					setValue(pt.ptr, val, 'i32');
				}
				else if (pt.ptrType == 3)
				{
					setValue(pt.ptr, val, 'float');
				}
			}

			return singleValue;
		}
	},

	'nativeInit': function(hashString)
	{
		hashString = Pointer_stringify(hashString);

		nativeState = {
			hash: hashString,
			arguments: []
		};
	},

	'nativePushPtr': function(type, ptr)
	{
		nativeState.arguments.push(
		{
			type: 'ptr',
			ptrType: type,
			ptr: ptr
		});
	},

	'nativePushString': function(string)
	{
		nativeState.arguments.push({
			type: 'string',
			val: Pointer_stringify(string)
		});
	},

	'nativePushInt': function(val)
	{
		nativeState.arguments.push({
			type: 'int',
			val: val
		});
	},

	'nativePushFloat': function(val)
	{
		nativeState.arguments.push({
			type: 'float',
			val: (val === 0) ? val : val + 0.00001
		});
	},

	'Cfx_WrapMainFunction': function(fn)
	{
		print('Cfx_WrapMainFunction');

		setTimeout(function()
		{
			Runtime.dynCall('v', fn, []);
		}, 0);
	},

	'nativeCallInt': function()
	{
		return NATIVE.callNative(Citizen.resultAsInteger());
	},

	'nativeCallFloat': function()
	{
		return NATIVE.callNative(Citizen.resultAsFloat());
	},

	'nativeCallString': function()
	{
		'use strict';

		let str = NATIVE.callNative(Citizen.resultAsString());

		if (typeof window.stringPool === 'undefined')
		{
			window.stringPool = {};
		}

		if (!(str in window.stringPool))
		{
			let buffer = allocate(intArrayFromString(str), 'i8', ALLOC_NORMAL);

			window.stringPool[str] = buffer;
		}

		return window.stringPool[str];
	},

	'nativeCallVector3': function(pX, pY, pZ)
	{
		'use strict';

		let vector = NATIVE.callNative(Citizen.resultAsVector());

		setValue(pX, vector[0], 'float');
		setValue(pY, vector[1], 'float');
		setValue(pZ, vector[2], 'float');
	}
};

autoAddDeps(library, '$NATIVE');
mergeInto(LibraryManager.library, library);