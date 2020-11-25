#pragma once

#define SINGLE(Type) public:\
					static Type* GetInst()\
					{\
						static Type mgr;\
						return &mgr;\
					}\
					private:\
						Type();\
						~Type();


#define SINGLE_HEAP(Type) private:\
						static Type* g_pInstance;\
						public:\
						static Type* GetInst()\
						{\
							if (NULL == g_pInstance)\
							{\
								g_pInstance = new Type;\
							}\
						return g_pInstance;\
						}\
						static void DeleteInst()\
						{\
							if (NULL != g_pInstance)\
							{\
								delete g_pInstance;\
								g_pInstance = NULL;\
							}\
						}\
						private:\
							Type(); \
							~Type();