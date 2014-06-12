; ModuleID = 'examples/cp_branches/cp_branches_m.bc'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

@_ZZ4mainE3arr = private unnamed_addr constant [3 x i32] [i32 1, i32 2, i32 3], align 4

; Function Attrs: nounwind uwtable
define i32 @main() #0 {
entry:
  %arr = alloca [3 x i32], align 4
  %0 = bitcast [3 x i32]* %arr to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %0, i8* bitcast ([3 x i32]* @_ZZ4mainE3arr to i8*), i64 12, i32 4, i1 false)
  %arrayidx = getelementptr inbounds [3 x i32]* %arr, i32 0, i64 1
  %1 = load i32* %arrayidx, align 4
  %arrayidx1 = getelementptr inbounds [3 x i32]* %arr, i32 0, i64 2
  store i32 4, i32* %arrayidx1, align 4
  %arrayidx2 = getelementptr inbounds [3 x i32]* %arr, i32 0, i64 2
  %z = load i32* %arrayidx2, align 4
  %addr = sub i32 10, 7
  %cmp = icmp eq i32 %z, 9
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %y = mul i32 3, 5
  br label %if.end

if.else:                                          ; preds = %entry
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  %x.0 = phi i32 [ 4, %if.then ], [ 4, %if.else ]
  ret i32 0
}

; Function Attrs: nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #1

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"clang version 3.4 (tags/RELEASE_34/final)"}
