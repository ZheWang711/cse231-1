; ModuleID = '/home/cjtosh/cse231-proj1/extra/benchmarks/welcome/welcome2reg.bc'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @_Z1fi(i32 %y) #0 {
entry:
  %add0 = add nsw i32 2, %y
  %cmp = icmp sgt i32 %add0, 10
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %add1 = add nsw i32 20, %add0
  br label %if.end

if.else:                                          ; preds = %entry
  %add2 = add nsw i32 21, %add0
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %x = phi i32 [ %add1, %if.then ], [ %add2, %if.else ]
  ;%y.addr.0 = phi i32 [ %y, %if.then ], [ %add2, %if.else ]
  ;%addb = add nsw i32 2, %y	     	
  ;%x.1 = add nsw i32 20, %adda
  %add3 = add nsw i32 %x, %x
  ret i32 %add3
}

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"clang version 3.4 (tags/RELEASE_34/final)"}
