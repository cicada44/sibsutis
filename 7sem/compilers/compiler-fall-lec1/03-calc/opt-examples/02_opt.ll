; ModuleID = 'opt-examples/02.ll'
source_filename = "calc.expr"

@a.str = private constant [2 x i8] c"a\00"

define i32 @main(i32 %0, ptr nocapture readnone %1) local_unnamed_addr {
entry:
  %2 = tail call i32 @calc_read(ptr nonnull @a.str)
  %3 = shl nsw i32 %2, 2
  tail call void @calc_write(i32 %3)
  ret i32 0
}

declare i32 @calc_read(ptr) local_unnamed_addr

declare void @calc_write(i32) local_unnamed_addr
