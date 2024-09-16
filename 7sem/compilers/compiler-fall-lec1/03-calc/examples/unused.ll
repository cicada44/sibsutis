; ModuleID = 'calc.expr'
source_filename = "calc.expr"

@a.str = private constant [2 x i8] c"a\00"
@b.str = private constant [2 x i8] c"b\00"
@c.str = private constant [2 x i8] c"c\00"

define i32 @main(i32 %0, ptr %1) {
entry:
  %2 = call i32 @calc_read([2 x i8]* @a.str)
  %3 = call i32 @calc_read([2 x i8]* @b.str)
  %4 = call i32 @calc_read([2 x i8]* @c.str)
  %5 = add nsw i32 %2, %3
  call void @calc_write(i32 %5)
  ret i32 0
}

declare i32 @calc_read(ptr)

declare void @calc_write(i32)
