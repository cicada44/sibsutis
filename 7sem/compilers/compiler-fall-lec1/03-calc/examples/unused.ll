; ModuleID = 'calc.expr'
source_filename = "calc.expr"

@x.str = private constant [2 x i8] c"x\00"
@y.str = private constant [2 x i8] c"y\00"
@unused.str = private constant [7 x i8] c"unused\00"

define i32 @main(i32 %0, ptr %1) {
entry:
  %2 = call i32 @calc_read([2 x i8]* @x.str)
  %3 = call i32 @calc_read([2 x i8]* @y.str)
  %4 = call i32 @calc_read([7 x i8]* @unused.str)
  %5 = add nsw i32 %2, %3
  call void @calc_write(i32 %5)
  ret i32 0
}

declare i32 @calc_read(ptr)

declare void @calc_write(i32)
