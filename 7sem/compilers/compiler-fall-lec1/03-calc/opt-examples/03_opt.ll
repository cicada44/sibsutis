; ModuleID = 'opt-examples/03.ll'
source_filename = "calc.expr"

@x.str = private constant [2 x i8] c"x\00"
@y.str = private constant [2 x i8] c"y\00"

define i32 @main(i32 %0, ptr nocapture readnone %1) local_unnamed_addr {
entry:
  %2 = tail call i32 @calc_read(ptr nonnull @x.str)
  %3 = tail call i32 @calc_read(ptr nonnull @y.str)
  tail call void @calc_write(i32 0)
  ret i32 0
}

declare i32 @calc_read(ptr) local_unnamed_addr

declare void @calc_write(i32) local_unnamed_addr
