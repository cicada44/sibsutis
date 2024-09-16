; ModuleID = 'calc.expr'
source_filename = "calc.expr"

@x.str = private constant [2 x i8] c"x\00"
@y.str = private constant [2 x i8] c"y\00"

define i32 @main(i32 %0, ptr %1) {
entry:
  %2 = call i32 @calc_read([2 x i8]* @x.str)
  %3 = call i32 @calc_read([2 x i8]* @y.str)
  %4 = add nsw i32 %2, %3
  %5 = add nsw i32 %2, %3
  %6 = sub nsw i32 %4, %5
  call void @calc_write(i32 %6)
  ret i32 0
}

declare i32 @calc_read(ptr)

declare void @calc_write(i32)
