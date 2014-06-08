; ModuleID = 'extra/benchmarks/adding_with_pointers/adding_with_pointers.bc'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @_Z1fi(i32 %c) #0 {
entry:
  %a_1 = alloca i32, align 4
  %a_2 = alloca i32, align 4
  %x = add i32 1, 2
  store i32 15, i32* %a_1, align 4
  %y = add i32 -1, -2
  store i32 10, i32* %a_2, align 4
  %add = add i32 %x, %y
  ret i32 %add
}

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"clang version 3.4 (tags/RELEASE_34/final)"}
