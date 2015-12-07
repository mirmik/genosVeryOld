


#ifndef ENUM_OPERATIONS
	#define ENUM_OPERATIONS
	
		
	
#define DECLARE_ENUM_OPERATIONS(ENUM_NAME)                              \
inline constexpr ENUM_NAME                                                        \
operator|(ENUM_NAME left, ENUM_NAME right)                              \
{ return ENUM_NAME(static_cast<int>(left) | static_cast<int>(right)); } \
                                                                        \
inline constexpr ENUM_NAME                                                        \
operator&(ENUM_NAME left, ENUM_NAME right)                              \
{ return ENUM_NAME(static_cast<int>(left) & static_cast<int>(right)); } \
                                                                        \
inline constexpr ENUM_NAME                                                        \
operator^(ENUM_NAME left, ENUM_NAME right)                              \
{ return ENUM_NAME(static_cast<int>(left) ^ static_cast<int>(right)); } \
                                                                        \
inline constexpr ENUM_NAME                                                        \
operator~(ENUM_NAME left)                                               \
{ return ENUM_NAME(~static_cast<int>(left)); }                          \
                                                                        \
inline constexpr const ENUM_NAME&                                                 \
operator|=(ENUM_NAME& left, ENUM_NAME right)                            \
{ return left = left | right; }                                         \
                                                                        \
inline constexpr const ENUM_NAME&                                                 \
operator&=(ENUM_NAME& left, ENUM_NAME right)                            \
{ return left = left & right; }                                         \
                                                                        \
inline constexpr const ENUM_NAME&                                                 \
operator^=(ENUM_NAME& left, ENUM_NAME right)                            \
{ return left = left ^ right; }											\
																		\
	
	
	
	
	
	
	
#endif