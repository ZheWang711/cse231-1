; ModuleID = 'examples/pointer_loop/pointer_loop.bc'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @_Z1fi(i32 %x) #0 {
entry:
  %x.addr = alloca i32, align 4
  %a_1 = alloca i32, align 4
  %a_2 = alloca i32, align 4
  %b_1 = alloca i32*, align 8
  %b_2 = alloca i32*, align 8
  store i32 %x, i32* %x.addr, align 4
  store i32 10, i32* %a_1, align 4
  store i32 15, i32* %a_2, align 4
  store i32* %a_1, i32** %b_1, align 8
  store i32* %a_2, i32** %b_2, align 8
  br label %while.cond

while.cond:                                       ; preds = %while.body, %entry
  %0 = load i32* %a_1, align 4
  %cmp = icmp slt i32 %0, 100
  br i1 %cmp, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %1 = load i32* %a_1, align 4
  %add = add nsw i32 %1, 1
  store i32 %add, i32* %a_1, align 4
  %2 = load i32* %a_1, align 4
  %3 = load i32** %b_2, align 8
  store i32 %2, i32* %3, align 4
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %4 = load i32* %a_2, align 4
  ret i32 %4
}

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"clang version 3.4 (tags/RELEASE_34/final)"}
