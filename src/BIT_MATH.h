//file guard
#ifndef BIT_MATH_H
#define BIT_MATH_H

#define set_bit(VAR,BitNo) VAR|=(1<<BitNo)
#define clear_bit(VAR,BitNo) VAR&=(~(1<<BitNo))
#define toggle_bit(VAR,BitNo) VAR^=(1<<BitNo)
#define get_bit(VAR,BitNo) (VAR&(1<<BitNo))>>BitNo

#endif
