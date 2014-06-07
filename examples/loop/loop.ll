; ModuleID = 'examples/loop/loop.bc'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @_Z1fi(i32 %x) #0 {
entry:
  %y = add nsw i32 0, 0
  %i = add nsw i32 0, 0
  br label %while.cond

while.cond:                                       ; preds = %while.body, %entry
  %i.0 = phi i32 [ %i, %entry ], [ %add1, %while.body ]
  %x.addr.0 = phi i32 [ %y, %entry ], [ %add, %while.body ]
  %cmp = icmp slt i32 %i.0, 3
  br i1 %cmp, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %add = add nsw i32 %x.addr.0, %i.0
  %add1 = add nsw i32 %i.0, 1
  br label %while.cond

while.end:                                        ; preds = %while.cond
  ret i32 %x.addr.0
}

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"clang version 3.4 (tags/RELEASE_34/final)"}
