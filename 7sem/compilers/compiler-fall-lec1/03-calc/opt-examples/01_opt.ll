; ModuleID = 'opt-examples/01.ll'
source_filename = "calc.expr"

define i32 @main(i32 %0, ptr nocapture readnone %1) local_unnamed_addr {
entry:
  tail call void @calc_write(i32 6)
  ret i32 0
}

declare void @calc_write(i32) local_unnamed_addr
