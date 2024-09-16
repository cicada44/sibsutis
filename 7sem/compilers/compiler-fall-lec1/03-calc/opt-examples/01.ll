; ModuleID = 'calc.expr'
source_filename = "calc.expr"

define i32 @main(i32 %0, ptr %1) {
entry:
  call void @calc_write(i32 6)
  ret i32 0
}

declare void @calc_write(i32)
