; ModuleID = 'examples/array_access/array_access_success.bc'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

; Function Attrs: nounwind uwtable
define i32 @_Z1fi(i32 %x) #0 {
entry:
  %a = alloca [10 x i32], align 16
  br label %while.cond

while.cond:                                       ; preds = %while.body, %entry
  %i.0 = phi i32 [ 0, %entry ], [ %add, %while.body ]
  %z.0 = phi i32 [ 0, %entry ], [ %add1, %while.body ]
  %cmp = icmp slt i32 %i.0, 6
  br i1 %cmp, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %idxprom = sext i32 %i.0 to i64
  %arrayidx = getelementptr inbounds [10 x i32]* %a, i32 0, i64 %idxprom
  store i32 2, i32* %arrayidx, align 4
  %add = add nsw i32 %i.0, 1
  %add1 = add nsw i32 %z.0, 3
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %cmp2 = icmp slt i32 %z.0, 10
  br i1 %cmp2, label %if.then, label %if.end7

if.then:                                          ; preds = %while.end
  %cmp3 = icmp sge i32 %z.0, 0
  br i1 %cmp3, label %if.then4, label %if.end

if.then4:                                         ; preds = %if.then
  %idxprom5 = sext i32 %z.0 to i64
  %arrayidx6 = getelementptr inbounds [10 x i32]* %a, i32 0, i64 %idxprom5
  store i32 20, i32* %arrayidx6, align 4
  br label %if.end

if.end:                                           ; preds = %if.then4, %if.then
  br label %if.end7

if.end7:                                          ; preds = %if.end, %while.end
  %arrayidx8 = getelementptr inbounds [10 x i32]* %a, i32 0, i64 3
  %0 = load i32* %arrayidx8, align 4
  ret i32 %0
}

attributes #0 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"clang version 3.4 (tags/RELEASE_34/final)"}
