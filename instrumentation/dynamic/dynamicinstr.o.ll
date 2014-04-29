; ModuleID = 'dynamicinstr.o'
target datalayout = "e-p:64:64:64-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-v64:64:64-v128:128:128-a0:0:64-s0:64:64-f80:128:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%"class.std::ios_base::Init" = type { i8 }
%"class.std::map" = type { %"class.std::_Rb_tree" }
%"class.std::_Rb_tree" = type { %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl" }
%"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl" = type { %"struct.std::less", %"struct.std::_Rb_tree_node_base", i64 }
%"struct.std::less" = type { i8 }
%"struct.std::_Rb_tree_node_base" = type { i32, %"struct.std::_Rb_tree_node_base"*, %"struct.std::_Rb_tree_node_base"*, %"struct.std::_Rb_tree_node_base"* }
%"struct.std::_Rb_tree_const_iterator" = type { %"struct.std::_Rb_tree_node_base"* }
%"struct.std::_Rb_tree_iterator" = type { %"struct.std::_Rb_tree_node_base"* }
%"struct.std::pair" = type { i32, i32 }
%"struct.std::_Rb_tree_node" = type { %"struct.std::_Rb_tree_node_base", %"struct.std::pair" }
%"struct.std::_Select1st" = type { i8 }
%"struct.std::pair.0" = type { %"struct.std::_Rb_tree_iterator", i8 }
%"class.std::allocator.1" = type { i8 }
%"class.__gnu_cxx::new_allocator.2" = type { i8 }
%"class.std::allocator" = type { i8 }
%"class.__gnu_cxx::new_allocator" = type { i8 }

@_ZStL8__ioinit = internal global %"class.std::ios_base::Init" zeroinitializer, align 1
@__dso_handle = external unnamed_addr global i8
@instExCount = global %"class.std::map" zeroinitializer, align 8
@.str = private unnamed_addr constant [25 x i8] c"Instruction\09Executions\09\0A\00", align 1
@llvm.global_ctors = appending global [1 x { i32, void ()* }] [{ i32, void ()* } { i32 65535, void ()* @_GLOBAL__I_a }]

define internal void @__cxx_global_var_init() section ".text.startup" {
entry:
  call void @_ZNSt8ios_base4InitC1Ev(%"class.std::ios_base::Init"* @_ZStL8__ioinit)
  %0 = call i32 @__cxa_atexit(void (i8*)* bitcast (void (%"class.std::ios_base::Init"*)* @_ZNSt8ios_base4InitD1Ev to void (i8*)*), i8* getelementptr inbounds (%"class.std::ios_base::Init"* @_ZStL8__ioinit, i32 0, i32 0), i8* @__dso_handle) #1
  ret void
}

declare void @_ZNSt8ios_base4InitC1Ev(%"class.std::ios_base::Init"*) #0

declare void @_ZNSt8ios_base4InitD1Ev(%"class.std::ios_base::Init"*) #0

; Function Attrs: nounwind
declare i32 @__cxa_atexit(void (i8*)*, i8*, i8*) #1

define internal void @__cxx_global_var_init1() section ".text.startup" {
entry:
  call void @_ZNSt3mapIiiSt4lessIiESaISt4pairIKiiEEEC2Ev(%"class.std::map"* @instExCount)
  %0 = call i32 @__cxa_atexit(void (i8*)* bitcast (void (%"class.std::map"*)* @_ZNSt3mapIiiSt4lessIiESaISt4pairIKiiEEED2Ev to void (i8*)*), i8* getelementptr inbounds (%"class.std::map"* @instExCount, i32 0, i32 0, i32 0, i32 0, i32 0), i8* @__dso_handle) #1
  ret void
}

; Function Attrs: uwtable
define linkonce_odr void @_ZNSt3mapIiiSt4lessIiESaISt4pairIKiiEEEC2Ev(%"class.std::map"* %this) unnamed_addr #2 align 2 {
entry:
  %this.addr = alloca %"class.std::map"*, align 8
  store %"class.std::map"* %this, %"class.std::map"** %this.addr, align 8
  %this1 = load %"class.std::map"** %this.addr
  %_M_t = getelementptr inbounds %"class.std::map"* %this1, i32 0, i32 0
  call void @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EEC2Ev(%"class.std::_Rb_tree"* %_M_t)
  ret void
}

; Function Attrs: inlinehint uwtable
define linkonce_odr void @_ZNSt3mapIiiSt4lessIiESaISt4pairIKiiEEED2Ev(%"class.std::map"* %this) unnamed_addr #3 align 2 {
entry:
  %this.addr = alloca %"class.std::map"*, align 8
  store %"class.std::map"* %this, %"class.std::map"** %this.addr, align 8
  %this1 = load %"class.std::map"** %this.addr
  %_M_t = getelementptr inbounds %"class.std::map"* %this1, i32 0, i32 0
  call void @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EED2Ev(%"class.std::_Rb_tree"* %_M_t)
  ret void
}

; Function Attrs: uwtable
define void @_Z15printEverythingv() #2 {
entry:
  %call = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([25 x i8]* @.str, i32 0, i32 0))
  ret void
}

declare i32 @printf(i8*, ...) #0

; Function Attrs: uwtable
define void @_Z17countInstExecutedi(i32 %instOpcode) #2 {
entry:
  %instOpcode.addr = alloca i32, align 4
  store i32 %instOpcode, i32* %instOpcode.addr, align 4
  %call = call i64 @_ZNKSt3mapIiiSt4lessIiESaISt4pairIKiiEEE5countERS3_(%"class.std::map"* @instExCount, i32* %instOpcode.addr)
  %cmp = icmp ugt i64 %call, 0
  br i1 %cmp, label %if.then, label %if.else

if.then:                                          ; preds = %entry
  %call1 = call i32* @_ZNSt3mapIiiSt4lessIiESaISt4pairIKiiEEEixERS3_(%"class.std::map"* @instExCount, i32* %instOpcode.addr)
  %0 = load i32* %call1
  %add = add nsw i32 %0, 1
  %call2 = call i32* @_ZNSt3mapIiiSt4lessIiESaISt4pairIKiiEEEixERS3_(%"class.std::map"* @instExCount, i32* %instOpcode.addr)
  store i32 %add, i32* %call2
  br label %if.end

if.else:                                          ; preds = %entry
  %call3 = call i32* @_ZNSt3mapIiiSt4lessIiESaISt4pairIKiiEEEixERS3_(%"class.std::map"* @instExCount, i32* %instOpcode.addr)
  store i32 1, i32* %call3
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  ret void
}

; Function Attrs: uwtable
define linkonce_odr i64 @_ZNKSt3mapIiiSt4lessIiESaISt4pairIKiiEEE5countERS3_(%"class.std::map"* %this, i32* %__x) #2 align 2 {
entry:
  %this.addr = alloca %"class.std::map"*, align 8
  %__x.addr = alloca i32*, align 8
  %coerce = alloca %"struct.std::_Rb_tree_const_iterator", align 8
  %ref.tmp = alloca %"struct.std::_Rb_tree_const_iterator", align 8
  store %"class.std::map"* %this, %"class.std::map"** %this.addr, align 8
  store i32* %__x, i32** %__x.addr, align 8
  %this1 = load %"class.std::map"** %this.addr
  %_M_t = getelementptr inbounds %"class.std::map"* %this1, i32 0, i32 0
  %0 = load i32** %__x.addr, align 8
  %call = call %"struct.std::_Rb_tree_node_base"* @_ZNKSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE4findERS1_(%"class.std::_Rb_tree"* %_M_t, i32* %0)
  %coerce.dive = getelementptr %"struct.std::_Rb_tree_const_iterator"* %coerce, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %call, %"struct.std::_Rb_tree_node_base"** %coerce.dive
  %_M_t2 = getelementptr inbounds %"class.std::map"* %this1, i32 0, i32 0
  %call3 = call %"struct.std::_Rb_tree_node_base"* @_ZNKSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE3endEv(%"class.std::_Rb_tree"* %_M_t2)
  %coerce.dive4 = getelementptr %"struct.std::_Rb_tree_const_iterator"* %ref.tmp, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %call3, %"struct.std::_Rb_tree_node_base"** %coerce.dive4
  %call5 = call zeroext i1 @_ZNKSt23_Rb_tree_const_iteratorISt4pairIKiiEEeqERKS3_(%"struct.std::_Rb_tree_const_iterator"* %coerce, %"struct.std::_Rb_tree_const_iterator"* %ref.tmp)
  %cond = select i1 %call5, i32 0, i32 1
  %conv = sext i32 %cond to i64
  ret i64 %conv
}

; Function Attrs: uwtable
define linkonce_odr i32* @_ZNSt3mapIiiSt4lessIiESaISt4pairIKiiEEEixERS3_(%"class.std::map"* %this, i32* %__k) #2 align 2 {
entry:
  %this.addr = alloca %"class.std::map"*, align 8
  %__k.addr = alloca i32*, align 8
  %__i = alloca %"struct.std::_Rb_tree_iterator", align 8
  %ref.tmp = alloca %"struct.std::_Rb_tree_iterator", align 8
  %undef.agg.tmp = alloca %"struct.std::less", align 1
  %ref.tmp7 = alloca %"struct.std::_Rb_tree_iterator", align 8
  %agg.tmp = alloca %"struct.std::_Rb_tree_iterator", align 8
  %ref.tmp8 = alloca %"struct.std::pair", align 4
  %ref.tmp9 = alloca i32, align 4
  store %"class.std::map"* %this, %"class.std::map"** %this.addr, align 8
  store i32* %__k, i32** %__k.addr, align 8
  %this1 = load %"class.std::map"** %this.addr
  %0 = load i32** %__k.addr, align 8
  %call = call %"struct.std::_Rb_tree_node_base"* @_ZNSt3mapIiiSt4lessIiESaISt4pairIKiiEEE11lower_boundERS3_(%"class.std::map"* %this1, i32* %0)
  %coerce.dive = getelementptr %"struct.std::_Rb_tree_iterator"* %__i, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %call, %"struct.std::_Rb_tree_node_base"** %coerce.dive
  %call2 = call %"struct.std::_Rb_tree_node_base"* @_ZNSt3mapIiiSt4lessIiESaISt4pairIKiiEEE3endEv(%"class.std::map"* %this1)
  %coerce.dive3 = getelementptr %"struct.std::_Rb_tree_iterator"* %ref.tmp, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %call2, %"struct.std::_Rb_tree_node_base"** %coerce.dive3
  %call4 = call zeroext i1 @_ZNKSt17_Rb_tree_iteratorISt4pairIKiiEEeqERKS3_(%"struct.std::_Rb_tree_iterator"* %__i, %"struct.std::_Rb_tree_iterator"* %ref.tmp)
  br i1 %call4, label %if.then, label %lor.lhs.false

lor.lhs.false:                                    ; preds = %entry
  call void @_ZNKSt3mapIiiSt4lessIiESaISt4pairIKiiEEE8key_compEv(%"class.std::map"* %this1)
  %1 = load i32** %__k.addr, align 8
  %call5 = call %"struct.std::pair"* @_ZNKSt17_Rb_tree_iteratorISt4pairIKiiEEdeEv(%"struct.std::_Rb_tree_iterator"* %__i)
  %first = getelementptr inbounds %"struct.std::pair"* %call5, i32 0, i32 0
  %call6 = call zeroext i1 @_ZNKSt4lessIiEclERKiS2_(%"struct.std::less"* %undef.agg.tmp, i32* %1, i32* %first)
  br i1 %call6, label %if.then, label %if.end

if.then:                                          ; preds = %lor.lhs.false, %entry
  %2 = bitcast %"struct.std::_Rb_tree_iterator"* %agg.tmp to i8*
  %3 = bitcast %"struct.std::_Rb_tree_iterator"* %__i to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %2, i8* %3, i64 8, i32 8, i1 false)
  %4 = load i32** %__k.addr, align 8
  store i32 0, i32* %ref.tmp9
  call void @_ZNSt4pairIKiiEC2ERS0_S2_(%"struct.std::pair"* %ref.tmp8, i32* %4, i32* %ref.tmp9)
  %coerce.dive10 = getelementptr %"struct.std::_Rb_tree_iterator"* %agg.tmp, i32 0, i32 0
  %5 = load %"struct.std::_Rb_tree_node_base"** %coerce.dive10
  %call11 = call %"struct.std::_Rb_tree_node_base"* @_ZNSt3mapIiiSt4lessIiESaISt4pairIKiiEEE6insertESt17_Rb_tree_iteratorIS4_ERKS4_(%"class.std::map"* %this1, %"struct.std::_Rb_tree_node_base"* %5, %"struct.std::pair"* %ref.tmp8)
  %coerce.dive12 = getelementptr %"struct.std::_Rb_tree_iterator"* %ref.tmp7, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %call11, %"struct.std::_Rb_tree_node_base"** %coerce.dive12
  %6 = bitcast %"struct.std::_Rb_tree_iterator"* %__i to i8*
  %7 = bitcast %"struct.std::_Rb_tree_iterator"* %ref.tmp7 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %6, i8* %7, i64 8, i32 8, i1 false)
  br label %if.end

if.end:                                           ; preds = %if.then, %lor.lhs.false
  %call13 = call %"struct.std::pair"* @_ZNKSt17_Rb_tree_iteratorISt4pairIKiiEEdeEv(%"struct.std::_Rb_tree_iterator"* %__i)
  %second = getelementptr inbounds %"struct.std::pair"* %call13, i32 0, i32 1
  ret i32* %second
}

; Function Attrs: uwtable
define linkonce_odr %"struct.std::_Rb_tree_node_base"* @_ZNSt3mapIiiSt4lessIiESaISt4pairIKiiEEE11lower_boundERS3_(%"class.std::map"* %this, i32* %__x) #2 align 2 {
entry:
  %retval = alloca %"struct.std::_Rb_tree_iterator", align 8
  %this.addr = alloca %"class.std::map"*, align 8
  %__x.addr = alloca i32*, align 8
  store %"class.std::map"* %this, %"class.std::map"** %this.addr, align 8
  store i32* %__x, i32** %__x.addr, align 8
  %this1 = load %"class.std::map"** %this.addr
  %_M_t = getelementptr inbounds %"class.std::map"* %this1, i32 0, i32 0
  %0 = load i32** %__x.addr, align 8
  %call = call %"struct.std::_Rb_tree_node_base"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE11lower_boundERS1_(%"class.std::_Rb_tree"* %_M_t, i32* %0)
  %coerce.dive = getelementptr %"struct.std::_Rb_tree_iterator"* %retval, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %call, %"struct.std::_Rb_tree_node_base"** %coerce.dive
  %coerce.dive2 = getelementptr %"struct.std::_Rb_tree_iterator"* %retval, i32 0, i32 0
  %1 = load %"struct.std::_Rb_tree_node_base"** %coerce.dive2
  ret %"struct.std::_Rb_tree_node_base"* %1
}

; Function Attrs: nounwind uwtable
define linkonce_odr zeroext i1 @_ZNKSt17_Rb_tree_iteratorISt4pairIKiiEEeqERKS3_(%"struct.std::_Rb_tree_iterator"* %this, %"struct.std::_Rb_tree_iterator"* %__x) #4 align 2 {
entry:
  %this.addr = alloca %"struct.std::_Rb_tree_iterator"*, align 8
  %__x.addr = alloca %"struct.std::_Rb_tree_iterator"*, align 8
  store %"struct.std::_Rb_tree_iterator"* %this, %"struct.std::_Rb_tree_iterator"** %this.addr, align 8
  store %"struct.std::_Rb_tree_iterator"* %__x, %"struct.std::_Rb_tree_iterator"** %__x.addr, align 8
  %this1 = load %"struct.std::_Rb_tree_iterator"** %this.addr
  %_M_node = getelementptr inbounds %"struct.std::_Rb_tree_iterator"* %this1, i32 0, i32 0
  %0 = load %"struct.std::_Rb_tree_node_base"** %_M_node, align 8
  %1 = load %"struct.std::_Rb_tree_iterator"** %__x.addr, align 8
  %_M_node2 = getelementptr inbounds %"struct.std::_Rb_tree_iterator"* %1, i32 0, i32 0
  %2 = load %"struct.std::_Rb_tree_node_base"** %_M_node2, align 8
  %cmp = icmp eq %"struct.std::_Rb_tree_node_base"* %0, %2
  ret i1 %cmp
}

; Function Attrs: uwtable
define linkonce_odr %"struct.std::_Rb_tree_node_base"* @_ZNSt3mapIiiSt4lessIiESaISt4pairIKiiEEE3endEv(%"class.std::map"* %this) #2 align 2 {
entry:
  %retval = alloca %"struct.std::_Rb_tree_iterator", align 8
  %this.addr = alloca %"class.std::map"*, align 8
  store %"class.std::map"* %this, %"class.std::map"** %this.addr, align 8
  %this1 = load %"class.std::map"** %this.addr
  %_M_t = getelementptr inbounds %"class.std::map"* %this1, i32 0, i32 0
  %call = call %"struct.std::_Rb_tree_node_base"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE3endEv(%"class.std::_Rb_tree"* %_M_t)
  %coerce.dive = getelementptr %"struct.std::_Rb_tree_iterator"* %retval, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %call, %"struct.std::_Rb_tree_node_base"** %coerce.dive
  %coerce.dive2 = getelementptr %"struct.std::_Rb_tree_iterator"* %retval, i32 0, i32 0
  %0 = load %"struct.std::_Rb_tree_node_base"** %coerce.dive2
  ret %"struct.std::_Rb_tree_node_base"* %0
}

; Function Attrs: uwtable
define linkonce_odr void @_ZNKSt3mapIiiSt4lessIiESaISt4pairIKiiEEE8key_compEv(%"class.std::map"* %this) #2 align 2 {
entry:
  %retval = alloca %"struct.std::less", align 1
  %this.addr = alloca %"class.std::map"*, align 8
  %undef.agg.tmp = alloca %"struct.std::less", align 1
  store %"class.std::map"* %this, %"class.std::map"** %this.addr, align 8
  %this1 = load %"class.std::map"** %this.addr
  %_M_t = getelementptr inbounds %"class.std::map"* %this1, i32 0, i32 0
  call void @_ZNKSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE8key_compEv(%"class.std::_Rb_tree"* %_M_t)
  ret void
}

; Function Attrs: nounwind uwtable
define linkonce_odr zeroext i1 @_ZNKSt4lessIiEclERKiS2_(%"struct.std::less"* %this, i32* %__x, i32* %__y) #4 align 2 {
entry:
  %this.addr = alloca %"struct.std::less"*, align 8
  %__x.addr = alloca i32*, align 8
  %__y.addr = alloca i32*, align 8
  store %"struct.std::less"* %this, %"struct.std::less"** %this.addr, align 8
  store i32* %__x, i32** %__x.addr, align 8
  store i32* %__y, i32** %__y.addr, align 8
  %this1 = load %"struct.std::less"** %this.addr
  %0 = load i32** %__x.addr, align 8
  %1 = load i32* %0, align 4
  %2 = load i32** %__y.addr, align 8
  %3 = load i32* %2, align 4
  %cmp = icmp slt i32 %1, %3
  ret i1 %cmp
}

; Function Attrs: nounwind uwtable
define linkonce_odr %"struct.std::pair"* @_ZNKSt17_Rb_tree_iteratorISt4pairIKiiEEdeEv(%"struct.std::_Rb_tree_iterator"* %this) #4 align 2 {
entry:
  %this.addr = alloca %"struct.std::_Rb_tree_iterator"*, align 8
  store %"struct.std::_Rb_tree_iterator"* %this, %"struct.std::_Rb_tree_iterator"** %this.addr, align 8
  %this1 = load %"struct.std::_Rb_tree_iterator"** %this.addr
  %_M_node = getelementptr inbounds %"struct.std::_Rb_tree_iterator"* %this1, i32 0, i32 0
  %0 = load %"struct.std::_Rb_tree_node_base"** %_M_node, align 8
  %1 = bitcast %"struct.std::_Rb_tree_node_base"* %0 to %"struct.std::_Rb_tree_node"*
  %_M_value_field = getelementptr inbounds %"struct.std::_Rb_tree_node"* %1, i32 0, i32 1
  ret %"struct.std::pair"* %_M_value_field
}

; Function Attrs: uwtable
define linkonce_odr %"struct.std::_Rb_tree_node_base"* @_ZNSt3mapIiiSt4lessIiESaISt4pairIKiiEEE6insertESt17_Rb_tree_iteratorIS4_ERKS4_(%"class.std::map"* %this, %"struct.std::_Rb_tree_node_base"* %__position.coerce, %"struct.std::pair"* %__x) #2 align 2 {
entry:
  %retval = alloca %"struct.std::_Rb_tree_iterator", align 8
  %this.addr = alloca %"class.std::map"*, align 8
  %__position = alloca %"struct.std::_Rb_tree_iterator", align 8
  %__x.addr = alloca %"struct.std::pair"*, align 8
  %agg.tmp = alloca %"struct.std::_Rb_tree_const_iterator", align 8
  store %"class.std::map"* %this, %"class.std::map"** %this.addr, align 8
  %coerce.dive = getelementptr %"struct.std::_Rb_tree_iterator"* %__position, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %__position.coerce, %"struct.std::_Rb_tree_node_base"** %coerce.dive
  store %"struct.std::pair"* %__x, %"struct.std::pair"** %__x.addr, align 8
  %this1 = load %"class.std::map"** %this.addr
  %_M_t = getelementptr inbounds %"class.std::map"* %this1, i32 0, i32 0
  call void @_ZNSt23_Rb_tree_const_iteratorISt4pairIKiiEEC2ERKSt17_Rb_tree_iteratorIS2_E(%"struct.std::_Rb_tree_const_iterator"* %agg.tmp, %"struct.std::_Rb_tree_iterator"* %__position)
  %0 = load %"struct.std::pair"** %__x.addr, align 8
  %coerce.dive2 = getelementptr %"struct.std::_Rb_tree_const_iterator"* %agg.tmp, i32 0, i32 0
  %1 = load %"struct.std::_Rb_tree_node_base"** %coerce.dive2
  %call = call %"struct.std::_Rb_tree_node_base"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE17_M_insert_unique_ESt23_Rb_tree_const_iteratorIS2_ERKS2_(%"class.std::_Rb_tree"* %_M_t, %"struct.std::_Rb_tree_node_base"* %1, %"struct.std::pair"* %0)
  %coerce.dive3 = getelementptr %"struct.std::_Rb_tree_iterator"* %retval, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %call, %"struct.std::_Rb_tree_node_base"** %coerce.dive3
  %coerce.dive4 = getelementptr %"struct.std::_Rb_tree_iterator"* %retval, i32 0, i32 0
  %2 = load %"struct.std::_Rb_tree_node_base"** %coerce.dive4
  ret %"struct.std::_Rb_tree_node_base"* %2
}

; Function Attrs: nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #1

; Function Attrs: nounwind uwtable
define linkonce_odr void @_ZNSt4pairIKiiEC2ERS0_S2_(%"struct.std::pair"* %this, i32* %__a, i32* %__b) unnamed_addr #4 align 2 {
entry:
  %this.addr = alloca %"struct.std::pair"*, align 8
  %__a.addr = alloca i32*, align 8
  %__b.addr = alloca i32*, align 8
  store %"struct.std::pair"* %this, %"struct.std::pair"** %this.addr, align 8
  store i32* %__a, i32** %__a.addr, align 8
  store i32* %__b, i32** %__b.addr, align 8
  %this1 = load %"struct.std::pair"** %this.addr
  %first = getelementptr inbounds %"struct.std::pair"* %this1, i32 0, i32 0
  %0 = load i32** %__a.addr, align 8
  %1 = load i32* %0, align 4
  store i32 %1, i32* %first, align 4
  %second = getelementptr inbounds %"struct.std::pair"* %this1, i32 0, i32 1
  %2 = load i32** %__b.addr, align 8
  %3 = load i32* %2, align 4
  store i32 %3, i32* %second, align 4
  ret void
}

; Function Attrs: uwtable
define linkonce_odr %"struct.std::_Rb_tree_node_base"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE17_M_insert_unique_ESt23_Rb_tree_const_iteratorIS2_ERKS2_(%"class.std::_Rb_tree"* %this, %"struct.std::_Rb_tree_node_base"* %__position.coerce, %"struct.std::pair"* %__v) #2 align 2 {
entry:
  %retval = alloca %"struct.std::_Rb_tree_iterator", align 8
  %this.addr = alloca %"class.std::_Rb_tree"*, align 8
  %__position = alloca %"struct.std::_Rb_tree_const_iterator", align 8
  %__v.addr = alloca %"struct.std::pair"*, align 8
  %tmp = alloca %"struct.std::_Select1st", align 1
  %ref.tmp = alloca %"struct.std::pair.0", align 8
  %tmp16 = alloca %"struct.std::_Select1st", align 1
  %__before = alloca %"struct.std::_Rb_tree_const_iterator", align 8
  %tmp37 = alloca %"struct.std::_Select1st", align 1
  %ref.tmp54 = alloca %"struct.std::pair.0", align 8
  %tmp62 = alloca %"struct.std::_Select1st", align 1
  %__after = alloca %"struct.std::_Rb_tree_const_iterator", align 8
  %tmp77 = alloca %"struct.std::_Select1st", align 1
  %ref.tmp97 = alloca %"struct.std::pair.0", align 8
  store %"class.std::_Rb_tree"* %this, %"class.std::_Rb_tree"** %this.addr, align 8
  %coerce.dive = getelementptr %"struct.std::_Rb_tree_const_iterator"* %__position, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %__position.coerce, %"struct.std::_Rb_tree_node_base"** %coerce.dive
  store %"struct.std::pair"* %__v, %"struct.std::pair"** %__v.addr, align 8
  %this1 = load %"class.std::_Rb_tree"** %this.addr
  %_M_node = getelementptr inbounds %"struct.std::_Rb_tree_const_iterator"* %__position, i32 0, i32 0
  %0 = load %"struct.std::_Rb_tree_node_base"** %_M_node, align 8
  %call = call %"struct.std::_Rb_tree_node"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE6_M_endEv(%"class.std::_Rb_tree"* %this1)
  %1 = bitcast %"struct.std::_Rb_tree_node"* %call to %"struct.std::_Rb_tree_node_base"*
  %cmp = icmp eq %"struct.std::_Rb_tree_node_base"* %0, %1
  br i1 %cmp, label %if.then, label %if.else13

if.then:                                          ; preds = %entry
  %call2 = call i64 @_ZNKSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE4sizeEv(%"class.std::_Rb_tree"* %this1)
  %cmp3 = icmp ugt i64 %call2, 0
  br i1 %cmp3, label %land.lhs.true, label %if.else

land.lhs.true:                                    ; preds = %if.then
  %_M_impl = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  %_M_key_compare = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl, i32 0, i32 0
  %call4 = call %"struct.std::_Rb_tree_node_base"** @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE12_M_rightmostEv(%"class.std::_Rb_tree"* %this1)
  %2 = load %"struct.std::_Rb_tree_node_base"** %call4
  %call5 = call i32* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE6_S_keyEPKSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %2)
  %3 = load %"struct.std::pair"** %__v.addr, align 8
  %call6 = call i32* @_ZNKSt10_Select1stISt4pairIKiiEEclERKS2_(%"struct.std::_Select1st"* %tmp, %"struct.std::pair"* %3)
  %call7 = call zeroext i1 @_ZNKSt4lessIiEclERKiS2_(%"struct.std::less"* %_M_key_compare, i32* %call5, i32* %call6)
  br i1 %call7, label %if.then8, label %if.else

if.then8:                                         ; preds = %land.lhs.true
  %call9 = call %"struct.std::_Rb_tree_node_base"** @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE12_M_rightmostEv(%"class.std::_Rb_tree"* %this1)
  %4 = load %"struct.std::_Rb_tree_node_base"** %call9
  %5 = load %"struct.std::pair"** %__v.addr, align 8
  %call10 = call %"struct.std::_Rb_tree_node_base"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE10_M_insert_EPKSt18_Rb_tree_node_baseSB_RKS2_(%"class.std::_Rb_tree"* %this1, %"struct.std::_Rb_tree_node_base"* null, %"struct.std::_Rb_tree_node_base"* %4, %"struct.std::pair"* %5)
  %coerce.dive11 = getelementptr %"struct.std::_Rb_tree_iterator"* %retval, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %call10, %"struct.std::_Rb_tree_node_base"** %coerce.dive11
  br label %return

if.else:                                          ; preds = %land.lhs.true, %if.then
  %6 = load %"struct.std::pair"** %__v.addr, align 8
  %call12 = call { %"struct.std::_Rb_tree_node_base"*, i8 } @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE16_M_insert_uniqueERKS2_(%"class.std::_Rb_tree"* %this1, %"struct.std::pair"* %6)
  %7 = bitcast %"struct.std::pair.0"* %ref.tmp to { %"struct.std::_Rb_tree_node_base"*, i8 }*
  %8 = getelementptr { %"struct.std::_Rb_tree_node_base"*, i8 }* %7, i32 0, i32 0
  %9 = extractvalue { %"struct.std::_Rb_tree_node_base"*, i8 } %call12, 0
  store %"struct.std::_Rb_tree_node_base"* %9, %"struct.std::_Rb_tree_node_base"** %8, align 1
  %10 = getelementptr { %"struct.std::_Rb_tree_node_base"*, i8 }* %7, i32 0, i32 1
  %11 = extractvalue { %"struct.std::_Rb_tree_node_base"*, i8 } %call12, 1
  store i8 %11, i8* %10, align 1
  %first = getelementptr inbounds %"struct.std::pair.0"* %ref.tmp, i32 0, i32 0
  %12 = bitcast %"struct.std::_Rb_tree_iterator"* %retval to i8*
  %13 = bitcast %"struct.std::_Rb_tree_iterator"* %first to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %12, i8* %13, i64 8, i32 8, i1 false)
  br label %return

if.else13:                                        ; preds = %entry
  %_M_impl14 = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  %_M_key_compare15 = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl14, i32 0, i32 0
  %14 = load %"struct.std::pair"** %__v.addr, align 8
  %call17 = call i32* @_ZNKSt10_Select1stISt4pairIKiiEEclERKS2_(%"struct.std::_Select1st"* %tmp16, %"struct.std::pair"* %14)
  %_M_node18 = getelementptr inbounds %"struct.std::_Rb_tree_const_iterator"* %__position, i32 0, i32 0
  %15 = load %"struct.std::_Rb_tree_node_base"** %_M_node18, align 8
  %call19 = call i32* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE6_S_keyEPKSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %15)
  %call20 = call zeroext i1 @_ZNKSt4lessIiEclERKiS2_(%"struct.std::less"* %_M_key_compare15, i32* %call17, i32* %call19)
  br i1 %call20, label %if.then21, label %if.else57

if.then21:                                        ; preds = %if.else13
  %16 = bitcast %"struct.std::_Rb_tree_const_iterator"* %__before to i8*
  %17 = bitcast %"struct.std::_Rb_tree_const_iterator"* %__position to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %16, i8* %17, i64 8, i32 8, i1 false)
  %_M_node23 = getelementptr inbounds %"struct.std::_Rb_tree_const_iterator"* %__position, i32 0, i32 0
  %18 = load %"struct.std::_Rb_tree_node_base"** %_M_node23, align 8
  %call24 = call %"struct.std::_Rb_tree_node_base"** @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE11_M_leftmostEv(%"class.std::_Rb_tree"* %this1)
  %19 = load %"struct.std::_Rb_tree_node_base"** %call24
  %cmp25 = icmp eq %"struct.std::_Rb_tree_node_base"* %18, %19
  br i1 %cmp25, label %if.then26, label %if.else31

if.then26:                                        ; preds = %if.then21
  %call27 = call %"struct.std::_Rb_tree_node_base"** @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE11_M_leftmostEv(%"class.std::_Rb_tree"* %this1)
  %20 = load %"struct.std::_Rb_tree_node_base"** %call27
  %call28 = call %"struct.std::_Rb_tree_node_base"** @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE11_M_leftmostEv(%"class.std::_Rb_tree"* %this1)
  %21 = load %"struct.std::_Rb_tree_node_base"** %call28
  %22 = load %"struct.std::pair"** %__v.addr, align 8
  %call29 = call %"struct.std::_Rb_tree_node_base"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE10_M_insert_EPKSt18_Rb_tree_node_baseSB_RKS2_(%"class.std::_Rb_tree"* %this1, %"struct.std::_Rb_tree_node_base"* %20, %"struct.std::_Rb_tree_node_base"* %21, %"struct.std::pair"* %22)
  %coerce.dive30 = getelementptr %"struct.std::_Rb_tree_iterator"* %retval, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %call29, %"struct.std::_Rb_tree_node_base"** %coerce.dive30
  br label %return

if.else31:                                        ; preds = %if.then21
  %_M_impl32 = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  %_M_key_compare33 = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl32, i32 0, i32 0
  %call34 = call %"struct.std::_Rb_tree_const_iterator"* @_ZNSt23_Rb_tree_const_iteratorISt4pairIKiiEEmmEv(%"struct.std::_Rb_tree_const_iterator"* %__before)
  %_M_node35 = getelementptr inbounds %"struct.std::_Rb_tree_const_iterator"* %call34, i32 0, i32 0
  %23 = load %"struct.std::_Rb_tree_node_base"** %_M_node35, align 8
  %call36 = call i32* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE6_S_keyEPKSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %23)
  %24 = load %"struct.std::pair"** %__v.addr, align 8
  %call38 = call i32* @_ZNKSt10_Select1stISt4pairIKiiEEclERKS2_(%"struct.std::_Select1st"* %tmp37, %"struct.std::pair"* %24)
  %call39 = call zeroext i1 @_ZNKSt4lessIiEclERKiS2_(%"struct.std::less"* %_M_key_compare33, i32* %call36, i32* %call38)
  br i1 %call39, label %if.then40, label %if.else53

if.then40:                                        ; preds = %if.else31
  %_M_node41 = getelementptr inbounds %"struct.std::_Rb_tree_const_iterator"* %__before, i32 0, i32 0
  %25 = load %"struct.std::_Rb_tree_node_base"** %_M_node41, align 8
  %call42 = call %"struct.std::_Rb_tree_node"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE8_S_rightEPKSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %25)
  %cmp43 = icmp eq %"struct.std::_Rb_tree_node"* %call42, null
  br i1 %cmp43, label %if.then44, label %if.else48

if.then44:                                        ; preds = %if.then40
  %_M_node45 = getelementptr inbounds %"struct.std::_Rb_tree_const_iterator"* %__before, i32 0, i32 0
  %26 = load %"struct.std::_Rb_tree_node_base"** %_M_node45, align 8
  %27 = load %"struct.std::pair"** %__v.addr, align 8
  %call46 = call %"struct.std::_Rb_tree_node_base"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE10_M_insert_EPKSt18_Rb_tree_node_baseSB_RKS2_(%"class.std::_Rb_tree"* %this1, %"struct.std::_Rb_tree_node_base"* null, %"struct.std::_Rb_tree_node_base"* %26, %"struct.std::pair"* %27)
  %coerce.dive47 = getelementptr %"struct.std::_Rb_tree_iterator"* %retval, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %call46, %"struct.std::_Rb_tree_node_base"** %coerce.dive47
  br label %return

if.else48:                                        ; preds = %if.then40
  %_M_node49 = getelementptr inbounds %"struct.std::_Rb_tree_const_iterator"* %__position, i32 0, i32 0
  %28 = load %"struct.std::_Rb_tree_node_base"** %_M_node49, align 8
  %_M_node50 = getelementptr inbounds %"struct.std::_Rb_tree_const_iterator"* %__position, i32 0, i32 0
  %29 = load %"struct.std::_Rb_tree_node_base"** %_M_node50, align 8
  %30 = load %"struct.std::pair"** %__v.addr, align 8
  %call51 = call %"struct.std::_Rb_tree_node_base"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE10_M_insert_EPKSt18_Rb_tree_node_baseSB_RKS2_(%"class.std::_Rb_tree"* %this1, %"struct.std::_Rb_tree_node_base"* %28, %"struct.std::_Rb_tree_node_base"* %29, %"struct.std::pair"* %30)
  %coerce.dive52 = getelementptr %"struct.std::_Rb_tree_iterator"* %retval, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %call51, %"struct.std::_Rb_tree_node_base"** %coerce.dive52
  br label %return

if.else53:                                        ; preds = %if.else31
  %31 = load %"struct.std::pair"** %__v.addr, align 8
  %call55 = call { %"struct.std::_Rb_tree_node_base"*, i8 } @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE16_M_insert_uniqueERKS2_(%"class.std::_Rb_tree"* %this1, %"struct.std::pair"* %31)
  %32 = bitcast %"struct.std::pair.0"* %ref.tmp54 to { %"struct.std::_Rb_tree_node_base"*, i8 }*
  %33 = getelementptr { %"struct.std::_Rb_tree_node_base"*, i8 }* %32, i32 0, i32 0
  %34 = extractvalue { %"struct.std::_Rb_tree_node_base"*, i8 } %call55, 0
  store %"struct.std::_Rb_tree_node_base"* %34, %"struct.std::_Rb_tree_node_base"** %33, align 1
  %35 = getelementptr { %"struct.std::_Rb_tree_node_base"*, i8 }* %32, i32 0, i32 1
  %36 = extractvalue { %"struct.std::_Rb_tree_node_base"*, i8 } %call55, 1
  store i8 %36, i8* %35, align 1
  %first56 = getelementptr inbounds %"struct.std::pair.0"* %ref.tmp54, i32 0, i32 0
  %37 = bitcast %"struct.std::_Rb_tree_iterator"* %retval to i8*
  %38 = bitcast %"struct.std::_Rb_tree_iterator"* %first56 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %37, i8* %38, i64 8, i32 8, i1 false)
  br label %return

if.else57:                                        ; preds = %if.else13
  %_M_impl58 = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  %_M_key_compare59 = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl58, i32 0, i32 0
  %_M_node60 = getelementptr inbounds %"struct.std::_Rb_tree_const_iterator"* %__position, i32 0, i32 0
  %39 = load %"struct.std::_Rb_tree_node_base"** %_M_node60, align 8
  %call61 = call i32* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE6_S_keyEPKSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %39)
  %40 = load %"struct.std::pair"** %__v.addr, align 8
  %call63 = call i32* @_ZNKSt10_Select1stISt4pairIKiiEEclERKS2_(%"struct.std::_Select1st"* %tmp62, %"struct.std::pair"* %40)
  %call64 = call zeroext i1 @_ZNKSt4lessIiEclERKiS2_(%"struct.std::less"* %_M_key_compare59, i32* %call61, i32* %call63)
  br i1 %call64, label %if.then65, label %if.else100

if.then65:                                        ; preds = %if.else57
  %41 = bitcast %"struct.std::_Rb_tree_const_iterator"* %__after to i8*
  %42 = bitcast %"struct.std::_Rb_tree_const_iterator"* %__position to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %41, i8* %42, i64 8, i32 8, i1 false)
  %_M_node67 = getelementptr inbounds %"struct.std::_Rb_tree_const_iterator"* %__position, i32 0, i32 0
  %43 = load %"struct.std::_Rb_tree_node_base"** %_M_node67, align 8
  %call68 = call %"struct.std::_Rb_tree_node_base"** @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE12_M_rightmostEv(%"class.std::_Rb_tree"* %this1)
  %44 = load %"struct.std::_Rb_tree_node_base"** %call68
  %cmp69 = icmp eq %"struct.std::_Rb_tree_node_base"* %43, %44
  br i1 %cmp69, label %if.then70, label %if.else74

if.then70:                                        ; preds = %if.then65
  %call71 = call %"struct.std::_Rb_tree_node_base"** @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE12_M_rightmostEv(%"class.std::_Rb_tree"* %this1)
  %45 = load %"struct.std::_Rb_tree_node_base"** %call71
  %46 = load %"struct.std::pair"** %__v.addr, align 8
  %call72 = call %"struct.std::_Rb_tree_node_base"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE10_M_insert_EPKSt18_Rb_tree_node_baseSB_RKS2_(%"class.std::_Rb_tree"* %this1, %"struct.std::_Rb_tree_node_base"* null, %"struct.std::_Rb_tree_node_base"* %45, %"struct.std::pair"* %46)
  %coerce.dive73 = getelementptr %"struct.std::_Rb_tree_iterator"* %retval, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %call72, %"struct.std::_Rb_tree_node_base"** %coerce.dive73
  br label %return

if.else74:                                        ; preds = %if.then65
  %_M_impl75 = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  %_M_key_compare76 = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl75, i32 0, i32 0
  %47 = load %"struct.std::pair"** %__v.addr, align 8
  %call78 = call i32* @_ZNKSt10_Select1stISt4pairIKiiEEclERKS2_(%"struct.std::_Select1st"* %tmp77, %"struct.std::pair"* %47)
  %call79 = call %"struct.std::_Rb_tree_const_iterator"* @_ZNSt23_Rb_tree_const_iteratorISt4pairIKiiEEppEv(%"struct.std::_Rb_tree_const_iterator"* %__after)
  %_M_node80 = getelementptr inbounds %"struct.std::_Rb_tree_const_iterator"* %call79, i32 0, i32 0
  %48 = load %"struct.std::_Rb_tree_node_base"** %_M_node80, align 8
  %call81 = call i32* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE6_S_keyEPKSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %48)
  %call82 = call zeroext i1 @_ZNKSt4lessIiEclERKiS2_(%"struct.std::less"* %_M_key_compare76, i32* %call78, i32* %call81)
  br i1 %call82, label %if.then83, label %if.else96

if.then83:                                        ; preds = %if.else74
  %_M_node84 = getelementptr inbounds %"struct.std::_Rb_tree_const_iterator"* %__position, i32 0, i32 0
  %49 = load %"struct.std::_Rb_tree_node_base"** %_M_node84, align 8
  %call85 = call %"struct.std::_Rb_tree_node"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE8_S_rightEPKSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %49)
  %cmp86 = icmp eq %"struct.std::_Rb_tree_node"* %call85, null
  br i1 %cmp86, label %if.then87, label %if.else91

if.then87:                                        ; preds = %if.then83
  %_M_node88 = getelementptr inbounds %"struct.std::_Rb_tree_const_iterator"* %__position, i32 0, i32 0
  %50 = load %"struct.std::_Rb_tree_node_base"** %_M_node88, align 8
  %51 = load %"struct.std::pair"** %__v.addr, align 8
  %call89 = call %"struct.std::_Rb_tree_node_base"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE10_M_insert_EPKSt18_Rb_tree_node_baseSB_RKS2_(%"class.std::_Rb_tree"* %this1, %"struct.std::_Rb_tree_node_base"* null, %"struct.std::_Rb_tree_node_base"* %50, %"struct.std::pair"* %51)
  %coerce.dive90 = getelementptr %"struct.std::_Rb_tree_iterator"* %retval, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %call89, %"struct.std::_Rb_tree_node_base"** %coerce.dive90
  br label %return

if.else91:                                        ; preds = %if.then83
  %_M_node92 = getelementptr inbounds %"struct.std::_Rb_tree_const_iterator"* %__after, i32 0, i32 0
  %52 = load %"struct.std::_Rb_tree_node_base"** %_M_node92, align 8
  %_M_node93 = getelementptr inbounds %"struct.std::_Rb_tree_const_iterator"* %__after, i32 0, i32 0
  %53 = load %"struct.std::_Rb_tree_node_base"** %_M_node93, align 8
  %54 = load %"struct.std::pair"** %__v.addr, align 8
  %call94 = call %"struct.std::_Rb_tree_node_base"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE10_M_insert_EPKSt18_Rb_tree_node_baseSB_RKS2_(%"class.std::_Rb_tree"* %this1, %"struct.std::_Rb_tree_node_base"* %52, %"struct.std::_Rb_tree_node_base"* %53, %"struct.std::pair"* %54)
  %coerce.dive95 = getelementptr %"struct.std::_Rb_tree_iterator"* %retval, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %call94, %"struct.std::_Rb_tree_node_base"** %coerce.dive95
  br label %return

if.else96:                                        ; preds = %if.else74
  %55 = load %"struct.std::pair"** %__v.addr, align 8
  %call98 = call { %"struct.std::_Rb_tree_node_base"*, i8 } @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE16_M_insert_uniqueERKS2_(%"class.std::_Rb_tree"* %this1, %"struct.std::pair"* %55)
  %56 = bitcast %"struct.std::pair.0"* %ref.tmp97 to { %"struct.std::_Rb_tree_node_base"*, i8 }*
  %57 = getelementptr { %"struct.std::_Rb_tree_node_base"*, i8 }* %56, i32 0, i32 0
  %58 = extractvalue { %"struct.std::_Rb_tree_node_base"*, i8 } %call98, 0
  store %"struct.std::_Rb_tree_node_base"* %58, %"struct.std::_Rb_tree_node_base"** %57, align 1
  %59 = getelementptr { %"struct.std::_Rb_tree_node_base"*, i8 }* %56, i32 0, i32 1
  %60 = extractvalue { %"struct.std::_Rb_tree_node_base"*, i8 } %call98, 1
  store i8 %60, i8* %59, align 1
  %first99 = getelementptr inbounds %"struct.std::pair.0"* %ref.tmp97, i32 0, i32 0
  %61 = bitcast %"struct.std::_Rb_tree_iterator"* %retval to i8*
  %62 = bitcast %"struct.std::_Rb_tree_iterator"* %first99 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %61, i8* %62, i64 8, i32 8, i1 false)
  br label %return

if.else100:                                       ; preds = %if.else57
  %call101 = call %"struct.std::_Rb_tree_node_base"* @_ZNKSt23_Rb_tree_const_iteratorISt4pairIKiiEE13_M_const_castEv(%"struct.std::_Rb_tree_const_iterator"* %__position)
  %coerce.dive102 = getelementptr %"struct.std::_Rb_tree_iterator"* %retval, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %call101, %"struct.std::_Rb_tree_node_base"** %coerce.dive102
  br label %return

return:                                           ; preds = %if.else100, %if.else96, %if.else91, %if.then87, %if.then70, %if.else53, %if.else48, %if.then44, %if.then26, %if.else, %if.then8
  %coerce.dive103 = getelementptr %"struct.std::_Rb_tree_iterator"* %retval, i32 0, i32 0
  %63 = load %"struct.std::_Rb_tree_node_base"** %coerce.dive103
  ret %"struct.std::_Rb_tree_node_base"* %63
}

; Function Attrs: nounwind uwtable
define linkonce_odr void @_ZNSt23_Rb_tree_const_iteratorISt4pairIKiiEEC2ERKSt17_Rb_tree_iteratorIS2_E(%"struct.std::_Rb_tree_const_iterator"* %this, %"struct.std::_Rb_tree_iterator"* %__it) unnamed_addr #4 align 2 {
entry:
  %this.addr = alloca %"struct.std::_Rb_tree_const_iterator"*, align 8
  %__it.addr = alloca %"struct.std::_Rb_tree_iterator"*, align 8
  store %"struct.std::_Rb_tree_const_iterator"* %this, %"struct.std::_Rb_tree_const_iterator"** %this.addr, align 8
  store %"struct.std::_Rb_tree_iterator"* %__it, %"struct.std::_Rb_tree_iterator"** %__it.addr, align 8
  %this1 = load %"struct.std::_Rb_tree_const_iterator"** %this.addr
  %_M_node = getelementptr inbounds %"struct.std::_Rb_tree_const_iterator"* %this1, i32 0, i32 0
  %0 = load %"struct.std::_Rb_tree_iterator"** %__it.addr, align 8
  %_M_node2 = getelementptr inbounds %"struct.std::_Rb_tree_iterator"* %0, i32 0, i32 0
  %1 = load %"struct.std::_Rb_tree_node_base"** %_M_node2, align 8
  store %"struct.std::_Rb_tree_node_base"* %1, %"struct.std::_Rb_tree_node_base"** %_M_node, align 8
  ret void
}

; Function Attrs: nounwind uwtable
define linkonce_odr %"struct.std::_Rb_tree_node"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE6_M_endEv(%"class.std::_Rb_tree"* %this) #4 align 2 {
entry:
  %this.addr = alloca %"class.std::_Rb_tree"*, align 8
  store %"class.std::_Rb_tree"* %this, %"class.std::_Rb_tree"** %this.addr, align 8
  %this1 = load %"class.std::_Rb_tree"** %this.addr
  %_M_impl = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  %_M_header = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl, i32 0, i32 1
  %0 = bitcast %"struct.std::_Rb_tree_node_base"* %_M_header to %"struct.std::_Rb_tree_node"*
  ret %"struct.std::_Rb_tree_node"* %0
}

; Function Attrs: nounwind uwtable
define linkonce_odr i64 @_ZNKSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE4sizeEv(%"class.std::_Rb_tree"* %this) #4 align 2 {
entry:
  %this.addr = alloca %"class.std::_Rb_tree"*, align 8
  store %"class.std::_Rb_tree"* %this, %"class.std::_Rb_tree"** %this.addr, align 8
  %this1 = load %"class.std::_Rb_tree"** %this.addr
  %_M_impl = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  %_M_node_count = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl, i32 0, i32 2
  %0 = load i64* %_M_node_count, align 8
  ret i64 %0
}

; Function Attrs: uwtable
define linkonce_odr i32* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE6_S_keyEPKSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %__x) #2 align 2 {
entry:
  %__x.addr = alloca %"struct.std::_Rb_tree_node_base"*, align 8
  %tmp = alloca %"struct.std::_Select1st", align 1
  store %"struct.std::_Rb_tree_node_base"* %__x, %"struct.std::_Rb_tree_node_base"** %__x.addr, align 8
  %0 = load %"struct.std::_Rb_tree_node_base"** %__x.addr, align 8
  %call = call %"struct.std::pair"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE8_S_valueEPKSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %0)
  %call1 = call i32* @_ZNKSt10_Select1stISt4pairIKiiEEclERKS2_(%"struct.std::_Select1st"* %tmp, %"struct.std::pair"* %call)
  ret i32* %call1
}

; Function Attrs: nounwind uwtable
define linkonce_odr %"struct.std::_Rb_tree_node_base"** @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE12_M_rightmostEv(%"class.std::_Rb_tree"* %this) #4 align 2 {
entry:
  %this.addr = alloca %"class.std::_Rb_tree"*, align 8
  store %"class.std::_Rb_tree"* %this, %"class.std::_Rb_tree"** %this.addr, align 8
  %this1 = load %"class.std::_Rb_tree"** %this.addr
  %_M_impl = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  %_M_header = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl, i32 0, i32 1
  %_M_right = getelementptr inbounds %"struct.std::_Rb_tree_node_base"* %_M_header, i32 0, i32 3
  ret %"struct.std::_Rb_tree_node_base"** %_M_right
}

; Function Attrs: nounwind uwtable
define linkonce_odr i32* @_ZNKSt10_Select1stISt4pairIKiiEEclERKS2_(%"struct.std::_Select1st"* %this, %"struct.std::pair"* %__x) #4 align 2 {
entry:
  %this.addr = alloca %"struct.std::_Select1st"*, align 8
  %__x.addr = alloca %"struct.std::pair"*, align 8
  store %"struct.std::_Select1st"* %this, %"struct.std::_Select1st"** %this.addr, align 8
  store %"struct.std::pair"* %__x, %"struct.std::pair"** %__x.addr, align 8
  %this1 = load %"struct.std::_Select1st"** %this.addr
  %0 = load %"struct.std::pair"** %__x.addr, align 8
  %first = getelementptr inbounds %"struct.std::pair"* %0, i32 0, i32 0
  ret i32* %first
}

; Function Attrs: uwtable
define linkonce_odr %"struct.std::_Rb_tree_node_base"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE10_M_insert_EPKSt18_Rb_tree_node_baseSB_RKS2_(%"class.std::_Rb_tree"* %this, %"struct.std::_Rb_tree_node_base"* %__x, %"struct.std::_Rb_tree_node_base"* %__p, %"struct.std::pair"* %__v) #2 align 2 {
entry:
  %retval = alloca %"struct.std::_Rb_tree_iterator", align 8
  %this.addr = alloca %"class.std::_Rb_tree"*, align 8
  %__x.addr = alloca %"struct.std::_Rb_tree_node_base"*, align 8
  %__p.addr = alloca %"struct.std::_Rb_tree_node_base"*, align 8
  %__v.addr = alloca %"struct.std::pair"*, align 8
  %__insert_left = alloca i8, align 1
  %tmp = alloca %"struct.std::_Select1st", align 1
  %__z = alloca %"struct.std::_Rb_tree_node"*, align 8
  store %"class.std::_Rb_tree"* %this, %"class.std::_Rb_tree"** %this.addr, align 8
  store %"struct.std::_Rb_tree_node_base"* %__x, %"struct.std::_Rb_tree_node_base"** %__x.addr, align 8
  store %"struct.std::_Rb_tree_node_base"* %__p, %"struct.std::_Rb_tree_node_base"** %__p.addr, align 8
  store %"struct.std::pair"* %__v, %"struct.std::pair"** %__v.addr, align 8
  %this1 = load %"class.std::_Rb_tree"** %this.addr
  %0 = load %"struct.std::_Rb_tree_node_base"** %__x.addr, align 8
  %cmp = icmp ne %"struct.std::_Rb_tree_node_base"* %0, null
  br i1 %cmp, label %lor.end, label %lor.lhs.false

lor.lhs.false:                                    ; preds = %entry
  %1 = load %"struct.std::_Rb_tree_node_base"** %__p.addr, align 8
  %call = call %"struct.std::_Rb_tree_node"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE6_M_endEv(%"class.std::_Rb_tree"* %this1)
  %2 = bitcast %"struct.std::_Rb_tree_node"* %call to %"struct.std::_Rb_tree_node_base"*
  %cmp2 = icmp eq %"struct.std::_Rb_tree_node_base"* %1, %2
  br i1 %cmp2, label %lor.end, label %lor.rhs

lor.rhs:                                          ; preds = %lor.lhs.false
  %_M_impl = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  %_M_key_compare = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl, i32 0, i32 0
  %3 = load %"struct.std::pair"** %__v.addr, align 8
  %call3 = call i32* @_ZNKSt10_Select1stISt4pairIKiiEEclERKS2_(%"struct.std::_Select1st"* %tmp, %"struct.std::pair"* %3)
  %4 = load %"struct.std::_Rb_tree_node_base"** %__p.addr, align 8
  %call4 = call i32* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE6_S_keyEPKSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %4)
  %call5 = call zeroext i1 @_ZNKSt4lessIiEclERKiS2_(%"struct.std::less"* %_M_key_compare, i32* %call3, i32* %call4)
  br label %lor.end

lor.end:                                          ; preds = %lor.rhs, %lor.lhs.false, %entry
  %5 = phi i1 [ true, %lor.lhs.false ], [ true, %entry ], [ %call5, %lor.rhs ]
  %frombool = zext i1 %5 to i8
  store i8 %frombool, i8* %__insert_left, align 1
  %6 = load %"struct.std::pair"** %__v.addr, align 8
  %call7 = call %"struct.std::_Rb_tree_node"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE14_M_create_nodeERKS2_(%"class.std::_Rb_tree"* %this1, %"struct.std::pair"* %6)
  store %"struct.std::_Rb_tree_node"* %call7, %"struct.std::_Rb_tree_node"** %__z, align 8
  %7 = load i8* %__insert_left, align 1
  %tobool = trunc i8 %7 to i1
  %8 = load %"struct.std::_Rb_tree_node"** %__z, align 8
  %9 = bitcast %"struct.std::_Rb_tree_node"* %8 to %"struct.std::_Rb_tree_node_base"*
  %10 = load %"struct.std::_Rb_tree_node_base"** %__p.addr, align 8
  %_M_impl8 = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  %_M_header = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl8, i32 0, i32 1
  call void @_ZSt29_Rb_tree_insert_and_rebalancebPSt18_Rb_tree_node_baseS0_RS_(i1 zeroext %tobool, %"struct.std::_Rb_tree_node_base"* %9, %"struct.std::_Rb_tree_node_base"* %10, %"struct.std::_Rb_tree_node_base"* %_M_header) #1
  %_M_impl9 = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  %_M_node_count = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl9, i32 0, i32 2
  %11 = load i64* %_M_node_count, align 8
  %inc = add i64 %11, 1
  store i64 %inc, i64* %_M_node_count, align 8
  %12 = load %"struct.std::_Rb_tree_node"** %__z, align 8
  call void @_ZNSt17_Rb_tree_iteratorISt4pairIKiiEEC2EPSt13_Rb_tree_nodeIS2_E(%"struct.std::_Rb_tree_iterator"* %retval, %"struct.std::_Rb_tree_node"* %12)
  %coerce.dive = getelementptr %"struct.std::_Rb_tree_iterator"* %retval, i32 0, i32 0
  %13 = load %"struct.std::_Rb_tree_node_base"** %coerce.dive
  ret %"struct.std::_Rb_tree_node_base"* %13
}

; Function Attrs: uwtable
define linkonce_odr { %"struct.std::_Rb_tree_node_base"*, i8 } @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE16_M_insert_uniqueERKS2_(%"class.std::_Rb_tree"* %this, %"struct.std::pair"* %__v) #2 align 2 {
entry:
  %retval = alloca %"struct.std::pair.0", align 8
  %this.addr = alloca %"class.std::_Rb_tree"*, align 8
  %__v.addr = alloca %"struct.std::pair"*, align 8
  %__x = alloca %"struct.std::_Rb_tree_node"*, align 8
  %__y = alloca %"struct.std::_Rb_tree_node"*, align 8
  %__comp = alloca i8, align 1
  %tmp = alloca %"struct.std::_Select1st", align 1
  %__j = alloca %"struct.std::_Rb_tree_iterator", align 8
  %ref.tmp = alloca %"struct.std::_Rb_tree_iterator", align 8
  %ref.tmp13 = alloca %"struct.std::_Rb_tree_iterator", align 8
  %ref.tmp16 = alloca i8, align 1
  %tmp22 = alloca %"struct.std::_Select1st", align 1
  %ref.tmp26 = alloca %"struct.std::_Rb_tree_iterator", align 8
  %ref.tmp29 = alloca i8, align 1
  %ref.tmp31 = alloca i8, align 1
  store %"class.std::_Rb_tree"* %this, %"class.std::_Rb_tree"** %this.addr, align 8
  store %"struct.std::pair"* %__v, %"struct.std::pair"** %__v.addr, align 8
  %this1 = load %"class.std::_Rb_tree"** %this.addr
  %call = call %"struct.std::_Rb_tree_node"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE8_M_beginEv(%"class.std::_Rb_tree"* %this1)
  store %"struct.std::_Rb_tree_node"* %call, %"struct.std::_Rb_tree_node"** %__x, align 8
  %call2 = call %"struct.std::_Rb_tree_node"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE6_M_endEv(%"class.std::_Rb_tree"* %this1)
  store %"struct.std::_Rb_tree_node"* %call2, %"struct.std::_Rb_tree_node"** %__y, align 8
  store i8 1, i8* %__comp, align 1
  br label %while.cond

while.cond:                                       ; preds = %cond.end, %entry
  %0 = load %"struct.std::_Rb_tree_node"** %__x, align 8
  %cmp = icmp ne %"struct.std::_Rb_tree_node"* %0, null
  br i1 %cmp, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %1 = load %"struct.std::_Rb_tree_node"** %__x, align 8
  store %"struct.std::_Rb_tree_node"* %1, %"struct.std::_Rb_tree_node"** %__y, align 8
  %_M_impl = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  %_M_key_compare = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl, i32 0, i32 0
  %2 = load %"struct.std::pair"** %__v.addr, align 8
  %call3 = call i32* @_ZNKSt10_Select1stISt4pairIKiiEEclERKS2_(%"struct.std::_Select1st"* %tmp, %"struct.std::pair"* %2)
  %3 = load %"struct.std::_Rb_tree_node"** %__x, align 8
  %call4 = call i32* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE6_S_keyEPKSt13_Rb_tree_nodeIS2_E(%"struct.std::_Rb_tree_node"* %3)
  %call5 = call zeroext i1 @_ZNKSt4lessIiEclERKiS2_(%"struct.std::less"* %_M_key_compare, i32* %call3, i32* %call4)
  %frombool = zext i1 %call5 to i8
  store i8 %frombool, i8* %__comp, align 1
  %4 = load i8* %__comp, align 1
  %tobool = trunc i8 %4 to i1
  br i1 %tobool, label %cond.true, label %cond.false

cond.true:                                        ; preds = %while.body
  %5 = load %"struct.std::_Rb_tree_node"** %__x, align 8
  %6 = bitcast %"struct.std::_Rb_tree_node"* %5 to %"struct.std::_Rb_tree_node_base"*
  %call6 = call %"struct.std::_Rb_tree_node"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE7_S_leftEPSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %6)
  br label %cond.end

cond.false:                                       ; preds = %while.body
  %7 = load %"struct.std::_Rb_tree_node"** %__x, align 8
  %8 = bitcast %"struct.std::_Rb_tree_node"* %7 to %"struct.std::_Rb_tree_node_base"*
  %call7 = call %"struct.std::_Rb_tree_node"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE8_S_rightEPSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %8)
  br label %cond.end

cond.end:                                         ; preds = %cond.false, %cond.true
  %cond = phi %"struct.std::_Rb_tree_node"* [ %call6, %cond.true ], [ %call7, %cond.false ]
  store %"struct.std::_Rb_tree_node"* %cond, %"struct.std::_Rb_tree_node"** %__x, align 8
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %9 = load %"struct.std::_Rb_tree_node"** %__y, align 8
  call void @_ZNSt17_Rb_tree_iteratorISt4pairIKiiEEC2EPSt13_Rb_tree_nodeIS2_E(%"struct.std::_Rb_tree_iterator"* %__j, %"struct.std::_Rb_tree_node"* %9)
  %10 = load i8* %__comp, align 1
  %tobool9 = trunc i8 %10 to i1
  br i1 %tobool9, label %if.then, label %if.end18

if.then:                                          ; preds = %while.end
  %call10 = call %"struct.std::_Rb_tree_node_base"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE5beginEv(%"class.std::_Rb_tree"* %this1)
  %coerce.dive = getelementptr %"struct.std::_Rb_tree_iterator"* %ref.tmp, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %call10, %"struct.std::_Rb_tree_node_base"** %coerce.dive
  %call11 = call zeroext i1 @_ZNKSt17_Rb_tree_iteratorISt4pairIKiiEEeqERKS3_(%"struct.std::_Rb_tree_iterator"* %__j, %"struct.std::_Rb_tree_iterator"* %ref.tmp)
  br i1 %call11, label %if.then12, label %if.else

if.then12:                                        ; preds = %if.then
  %11 = load %"struct.std::_Rb_tree_node"** %__x, align 8
  %12 = bitcast %"struct.std::_Rb_tree_node"* %11 to %"struct.std::_Rb_tree_node_base"*
  %13 = load %"struct.std::_Rb_tree_node"** %__y, align 8
  %14 = bitcast %"struct.std::_Rb_tree_node"* %13 to %"struct.std::_Rb_tree_node_base"*
  %15 = load %"struct.std::pair"** %__v.addr, align 8
  %call14 = call %"struct.std::_Rb_tree_node_base"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE10_M_insert_EPKSt18_Rb_tree_node_baseSB_RKS2_(%"class.std::_Rb_tree"* %this1, %"struct.std::_Rb_tree_node_base"* %12, %"struct.std::_Rb_tree_node_base"* %14, %"struct.std::pair"* %15)
  %coerce.dive15 = getelementptr %"struct.std::_Rb_tree_iterator"* %ref.tmp13, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %call14, %"struct.std::_Rb_tree_node_base"** %coerce.dive15
  store i8 1, i8* %ref.tmp16
  call void @_ZNSt4pairISt17_Rb_tree_iteratorIS_IKiiEEbEC2ERKS3_RKb(%"struct.std::pair.0"* %retval, %"struct.std::_Rb_tree_iterator"* %ref.tmp13, i8* %ref.tmp16)
  br label %return

if.else:                                          ; preds = %if.then
  %call17 = call %"struct.std::_Rb_tree_iterator"* @_ZNSt17_Rb_tree_iteratorISt4pairIKiiEEmmEv(%"struct.std::_Rb_tree_iterator"* %__j)
  br label %if.end

if.end:                                           ; preds = %if.else
  br label %if.end18

if.end18:                                         ; preds = %if.end, %while.end
  %_M_impl19 = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  %_M_key_compare20 = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl19, i32 0, i32 0
  %_M_node = getelementptr inbounds %"struct.std::_Rb_tree_iterator"* %__j, i32 0, i32 0
  %16 = load %"struct.std::_Rb_tree_node_base"** %_M_node, align 8
  %call21 = call i32* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE6_S_keyEPKSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %16)
  %17 = load %"struct.std::pair"** %__v.addr, align 8
  %call23 = call i32* @_ZNKSt10_Select1stISt4pairIKiiEEclERKS2_(%"struct.std::_Select1st"* %tmp22, %"struct.std::pair"* %17)
  %call24 = call zeroext i1 @_ZNKSt4lessIiEclERKiS2_(%"struct.std::less"* %_M_key_compare20, i32* %call21, i32* %call23)
  br i1 %call24, label %if.then25, label %if.end30

if.then25:                                        ; preds = %if.end18
  %18 = load %"struct.std::_Rb_tree_node"** %__x, align 8
  %19 = bitcast %"struct.std::_Rb_tree_node"* %18 to %"struct.std::_Rb_tree_node_base"*
  %20 = load %"struct.std::_Rb_tree_node"** %__y, align 8
  %21 = bitcast %"struct.std::_Rb_tree_node"* %20 to %"struct.std::_Rb_tree_node_base"*
  %22 = load %"struct.std::pair"** %__v.addr, align 8
  %call27 = call %"struct.std::_Rb_tree_node_base"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE10_M_insert_EPKSt18_Rb_tree_node_baseSB_RKS2_(%"class.std::_Rb_tree"* %this1, %"struct.std::_Rb_tree_node_base"* %19, %"struct.std::_Rb_tree_node_base"* %21, %"struct.std::pair"* %22)
  %coerce.dive28 = getelementptr %"struct.std::_Rb_tree_iterator"* %ref.tmp26, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %call27, %"struct.std::_Rb_tree_node_base"** %coerce.dive28
  store i8 1, i8* %ref.tmp29
  call void @_ZNSt4pairISt17_Rb_tree_iteratorIS_IKiiEEbEC2ERKS3_RKb(%"struct.std::pair.0"* %retval, %"struct.std::_Rb_tree_iterator"* %ref.tmp26, i8* %ref.tmp29)
  br label %return

if.end30:                                         ; preds = %if.end18
  store i8 0, i8* %ref.tmp31
  call void @_ZNSt4pairISt17_Rb_tree_iteratorIS_IKiiEEbEC2ERKS3_RKb(%"struct.std::pair.0"* %retval, %"struct.std::_Rb_tree_iterator"* %__j, i8* %ref.tmp31)
  br label %return

return:                                           ; preds = %if.end30, %if.then25, %if.then12
  %23 = bitcast %"struct.std::pair.0"* %retval to { %"struct.std::_Rb_tree_node_base"*, i8 }*
  %24 = load { %"struct.std::_Rb_tree_node_base"*, i8 }* %23, align 1
  ret { %"struct.std::_Rb_tree_node_base"*, i8 } %24
}

; Function Attrs: nounwind uwtable
define linkonce_odr %"struct.std::_Rb_tree_node_base"** @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE11_M_leftmostEv(%"class.std::_Rb_tree"* %this) #4 align 2 {
entry:
  %this.addr = alloca %"class.std::_Rb_tree"*, align 8
  store %"class.std::_Rb_tree"* %this, %"class.std::_Rb_tree"** %this.addr, align 8
  %this1 = load %"class.std::_Rb_tree"** %this.addr
  %_M_impl = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  %_M_header = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl, i32 0, i32 1
  %_M_left = getelementptr inbounds %"struct.std::_Rb_tree_node_base"* %_M_header, i32 0, i32 2
  ret %"struct.std::_Rb_tree_node_base"** %_M_left
}

; Function Attrs: nounwind uwtable
define linkonce_odr %"struct.std::_Rb_tree_const_iterator"* @_ZNSt23_Rb_tree_const_iteratorISt4pairIKiiEEmmEv(%"struct.std::_Rb_tree_const_iterator"* %this) #4 align 2 {
entry:
  %this.addr = alloca %"struct.std::_Rb_tree_const_iterator"*, align 8
  store %"struct.std::_Rb_tree_const_iterator"* %this, %"struct.std::_Rb_tree_const_iterator"** %this.addr, align 8
  %this1 = load %"struct.std::_Rb_tree_const_iterator"** %this.addr
  %_M_node = getelementptr inbounds %"struct.std::_Rb_tree_const_iterator"* %this1, i32 0, i32 0
  %0 = load %"struct.std::_Rb_tree_node_base"** %_M_node, align 8
  %call = call %"struct.std::_Rb_tree_node_base"* @_ZSt18_Rb_tree_decrementPKSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %0) #12
  %_M_node2 = getelementptr inbounds %"struct.std::_Rb_tree_const_iterator"* %this1, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %call, %"struct.std::_Rb_tree_node_base"** %_M_node2, align 8
  ret %"struct.std::_Rb_tree_const_iterator"* %this1
}

; Function Attrs: nounwind uwtable
define linkonce_odr %"struct.std::_Rb_tree_node"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE8_S_rightEPKSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %__x) #4 align 2 {
entry:
  %__x.addr = alloca %"struct.std::_Rb_tree_node_base"*, align 8
  store %"struct.std::_Rb_tree_node_base"* %__x, %"struct.std::_Rb_tree_node_base"** %__x.addr, align 8
  %0 = load %"struct.std::_Rb_tree_node_base"** %__x.addr, align 8
  %_M_right = getelementptr inbounds %"struct.std::_Rb_tree_node_base"* %0, i32 0, i32 3
  %1 = load %"struct.std::_Rb_tree_node_base"** %_M_right, align 8
  %2 = bitcast %"struct.std::_Rb_tree_node_base"* %1 to %"struct.std::_Rb_tree_node"*
  ret %"struct.std::_Rb_tree_node"* %2
}

; Function Attrs: nounwind uwtable
define linkonce_odr %"struct.std::_Rb_tree_const_iterator"* @_ZNSt23_Rb_tree_const_iteratorISt4pairIKiiEEppEv(%"struct.std::_Rb_tree_const_iterator"* %this) #4 align 2 {
entry:
  %this.addr = alloca %"struct.std::_Rb_tree_const_iterator"*, align 8
  store %"struct.std::_Rb_tree_const_iterator"* %this, %"struct.std::_Rb_tree_const_iterator"** %this.addr, align 8
  %this1 = load %"struct.std::_Rb_tree_const_iterator"** %this.addr
  %_M_node = getelementptr inbounds %"struct.std::_Rb_tree_const_iterator"* %this1, i32 0, i32 0
  %0 = load %"struct.std::_Rb_tree_node_base"** %_M_node, align 8
  %call = call %"struct.std::_Rb_tree_node_base"* @_ZSt18_Rb_tree_incrementPKSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %0) #12
  %_M_node2 = getelementptr inbounds %"struct.std::_Rb_tree_const_iterator"* %this1, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %call, %"struct.std::_Rb_tree_node_base"** %_M_node2, align 8
  ret %"struct.std::_Rb_tree_const_iterator"* %this1
}

; Function Attrs: uwtable
define linkonce_odr %"struct.std::_Rb_tree_node_base"* @_ZNKSt23_Rb_tree_const_iteratorISt4pairIKiiEE13_M_const_castEv(%"struct.std::_Rb_tree_const_iterator"* %this) #2 align 2 {
entry:
  %retval = alloca %"struct.std::_Rb_tree_iterator", align 8
  %this.addr = alloca %"struct.std::_Rb_tree_const_iterator"*, align 8
  store %"struct.std::_Rb_tree_const_iterator"* %this, %"struct.std::_Rb_tree_const_iterator"** %this.addr, align 8
  %this1 = load %"struct.std::_Rb_tree_const_iterator"** %this.addr
  %_M_node = getelementptr inbounds %"struct.std::_Rb_tree_const_iterator"* %this1, i32 0, i32 0
  %0 = load %"struct.std::_Rb_tree_node_base"** %_M_node, align 8
  %1 = bitcast %"struct.std::_Rb_tree_node_base"* %0 to %"struct.std::_Rb_tree_node"*
  call void @_ZNSt17_Rb_tree_iteratorISt4pairIKiiEEC2EPSt13_Rb_tree_nodeIS2_E(%"struct.std::_Rb_tree_iterator"* %retval, %"struct.std::_Rb_tree_node"* %1)
  %coerce.dive = getelementptr %"struct.std::_Rb_tree_iterator"* %retval, i32 0, i32 0
  %2 = load %"struct.std::_Rb_tree_node_base"** %coerce.dive
  ret %"struct.std::_Rb_tree_node_base"* %2
}

; Function Attrs: nounwind uwtable
define linkonce_odr void @_ZNSt17_Rb_tree_iteratorISt4pairIKiiEEC2EPSt13_Rb_tree_nodeIS2_E(%"struct.std::_Rb_tree_iterator"* %this, %"struct.std::_Rb_tree_node"* %__x) unnamed_addr #4 align 2 {
entry:
  %this.addr = alloca %"struct.std::_Rb_tree_iterator"*, align 8
  %__x.addr = alloca %"struct.std::_Rb_tree_node"*, align 8
  store %"struct.std::_Rb_tree_iterator"* %this, %"struct.std::_Rb_tree_iterator"** %this.addr, align 8
  store %"struct.std::_Rb_tree_node"* %__x, %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  %this1 = load %"struct.std::_Rb_tree_iterator"** %this.addr
  %_M_node = getelementptr inbounds %"struct.std::_Rb_tree_iterator"* %this1, i32 0, i32 0
  %0 = load %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  %1 = bitcast %"struct.std::_Rb_tree_node"* %0 to %"struct.std::_Rb_tree_node_base"*
  store %"struct.std::_Rb_tree_node_base"* %1, %"struct.std::_Rb_tree_node_base"** %_M_node, align 8
  ret void
}

; Function Attrs: nounwind readonly
declare %"struct.std::_Rb_tree_node_base"* @_ZSt18_Rb_tree_incrementPKSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"*) #5

; Function Attrs: nounwind readonly
declare %"struct.std::_Rb_tree_node_base"* @_ZSt18_Rb_tree_decrementPKSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"*) #5

; Function Attrs: nounwind uwtable
define linkonce_odr %"struct.std::_Rb_tree_node"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE8_M_beginEv(%"class.std::_Rb_tree"* %this) #4 align 2 {
entry:
  %this.addr = alloca %"class.std::_Rb_tree"*, align 8
  store %"class.std::_Rb_tree"* %this, %"class.std::_Rb_tree"** %this.addr, align 8
  %this1 = load %"class.std::_Rb_tree"** %this.addr
  %_M_impl = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  %_M_header = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl, i32 0, i32 1
  %_M_parent = getelementptr inbounds %"struct.std::_Rb_tree_node_base"* %_M_header, i32 0, i32 1
  %0 = load %"struct.std::_Rb_tree_node_base"** %_M_parent, align 8
  %1 = bitcast %"struct.std::_Rb_tree_node_base"* %0 to %"struct.std::_Rb_tree_node"*
  ret %"struct.std::_Rb_tree_node"* %1
}

; Function Attrs: uwtable
define linkonce_odr i32* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE6_S_keyEPKSt13_Rb_tree_nodeIS2_E(%"struct.std::_Rb_tree_node"* %__x) #2 align 2 {
entry:
  %__x.addr = alloca %"struct.std::_Rb_tree_node"*, align 8
  %tmp = alloca %"struct.std::_Select1st", align 1
  store %"struct.std::_Rb_tree_node"* %__x, %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  %0 = load %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  %call = call %"struct.std::pair"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE8_S_valueEPKSt13_Rb_tree_nodeIS2_E(%"struct.std::_Rb_tree_node"* %0)
  %call1 = call i32* @_ZNKSt10_Select1stISt4pairIKiiEEclERKS2_(%"struct.std::_Select1st"* %tmp, %"struct.std::pair"* %call)
  ret i32* %call1
}

; Function Attrs: nounwind uwtable
define linkonce_odr %"struct.std::_Rb_tree_node"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE7_S_leftEPSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %__x) #4 align 2 {
entry:
  %__x.addr = alloca %"struct.std::_Rb_tree_node_base"*, align 8
  store %"struct.std::_Rb_tree_node_base"* %__x, %"struct.std::_Rb_tree_node_base"** %__x.addr, align 8
  %0 = load %"struct.std::_Rb_tree_node_base"** %__x.addr, align 8
  %_M_left = getelementptr inbounds %"struct.std::_Rb_tree_node_base"* %0, i32 0, i32 2
  %1 = load %"struct.std::_Rb_tree_node_base"** %_M_left, align 8
  %2 = bitcast %"struct.std::_Rb_tree_node_base"* %1 to %"struct.std::_Rb_tree_node"*
  ret %"struct.std::_Rb_tree_node"* %2
}

; Function Attrs: nounwind uwtable
define linkonce_odr %"struct.std::_Rb_tree_node"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE8_S_rightEPSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %__x) #4 align 2 {
entry:
  %__x.addr = alloca %"struct.std::_Rb_tree_node_base"*, align 8
  store %"struct.std::_Rb_tree_node_base"* %__x, %"struct.std::_Rb_tree_node_base"** %__x.addr, align 8
  %0 = load %"struct.std::_Rb_tree_node_base"** %__x.addr, align 8
  %_M_right = getelementptr inbounds %"struct.std::_Rb_tree_node_base"* %0, i32 0, i32 3
  %1 = load %"struct.std::_Rb_tree_node_base"** %_M_right, align 8
  %2 = bitcast %"struct.std::_Rb_tree_node_base"* %1 to %"struct.std::_Rb_tree_node"*
  ret %"struct.std::_Rb_tree_node"* %2
}

; Function Attrs: uwtable
define linkonce_odr %"struct.std::_Rb_tree_node_base"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE5beginEv(%"class.std::_Rb_tree"* %this) #2 align 2 {
entry:
  %retval = alloca %"struct.std::_Rb_tree_iterator", align 8
  %this.addr = alloca %"class.std::_Rb_tree"*, align 8
  store %"class.std::_Rb_tree"* %this, %"class.std::_Rb_tree"** %this.addr, align 8
  %this1 = load %"class.std::_Rb_tree"** %this.addr
  %_M_impl = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  %_M_header = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl, i32 0, i32 1
  %_M_left = getelementptr inbounds %"struct.std::_Rb_tree_node_base"* %_M_header, i32 0, i32 2
  %0 = load %"struct.std::_Rb_tree_node_base"** %_M_left, align 8
  %1 = bitcast %"struct.std::_Rb_tree_node_base"* %0 to %"struct.std::_Rb_tree_node"*
  call void @_ZNSt17_Rb_tree_iteratorISt4pairIKiiEEC2EPSt13_Rb_tree_nodeIS2_E(%"struct.std::_Rb_tree_iterator"* %retval, %"struct.std::_Rb_tree_node"* %1)
  %coerce.dive = getelementptr %"struct.std::_Rb_tree_iterator"* %retval, i32 0, i32 0
  %2 = load %"struct.std::_Rb_tree_node_base"** %coerce.dive
  ret %"struct.std::_Rb_tree_node_base"* %2
}

; Function Attrs: nounwind uwtable
define linkonce_odr void @_ZNSt4pairISt17_Rb_tree_iteratorIS_IKiiEEbEC2ERKS3_RKb(%"struct.std::pair.0"* %this, %"struct.std::_Rb_tree_iterator"* %__a, i8* %__b) unnamed_addr #4 align 2 {
entry:
  %this.addr = alloca %"struct.std::pair.0"*, align 8
  %__a.addr = alloca %"struct.std::_Rb_tree_iterator"*, align 8
  %__b.addr = alloca i8*, align 8
  store %"struct.std::pair.0"* %this, %"struct.std::pair.0"** %this.addr, align 8
  store %"struct.std::_Rb_tree_iterator"* %__a, %"struct.std::_Rb_tree_iterator"** %__a.addr, align 8
  store i8* %__b, i8** %__b.addr, align 8
  %this1 = load %"struct.std::pair.0"** %this.addr
  %first = getelementptr inbounds %"struct.std::pair.0"* %this1, i32 0, i32 0
  %0 = load %"struct.std::_Rb_tree_iterator"** %__a.addr, align 8
  %1 = bitcast %"struct.std::_Rb_tree_iterator"* %first to i8*
  %2 = bitcast %"struct.std::_Rb_tree_iterator"* %0 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %1, i8* %2, i64 8, i32 8, i1 false)
  %second = getelementptr inbounds %"struct.std::pair.0"* %this1, i32 0, i32 1
  %3 = load i8** %__b.addr, align 8
  %4 = load i8* %3, align 1
  %tobool = trunc i8 %4 to i1
  %frombool = zext i1 %tobool to i8
  store i8 %frombool, i8* %second, align 1
  ret void
}

; Function Attrs: nounwind uwtable
define linkonce_odr %"struct.std::_Rb_tree_iterator"* @_ZNSt17_Rb_tree_iteratorISt4pairIKiiEEmmEv(%"struct.std::_Rb_tree_iterator"* %this) #4 align 2 {
entry:
  %this.addr = alloca %"struct.std::_Rb_tree_iterator"*, align 8
  store %"struct.std::_Rb_tree_iterator"* %this, %"struct.std::_Rb_tree_iterator"** %this.addr, align 8
  %this1 = load %"struct.std::_Rb_tree_iterator"** %this.addr
  %_M_node = getelementptr inbounds %"struct.std::_Rb_tree_iterator"* %this1, i32 0, i32 0
  %0 = load %"struct.std::_Rb_tree_node_base"** %_M_node, align 8
  %call = call %"struct.std::_Rb_tree_node_base"* @_ZSt18_Rb_tree_decrementPSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %0) #12
  %_M_node2 = getelementptr inbounds %"struct.std::_Rb_tree_iterator"* %this1, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %call, %"struct.std::_Rb_tree_node_base"** %_M_node2, align 8
  ret %"struct.std::_Rb_tree_iterator"* %this1
}

; Function Attrs: nounwind readonly
declare %"struct.std::_Rb_tree_node_base"* @_ZSt18_Rb_tree_decrementPSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"*) #5

; Function Attrs: nounwind uwtable
define linkonce_odr %"struct.std::pair"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE8_S_valueEPKSt13_Rb_tree_nodeIS2_E(%"struct.std::_Rb_tree_node"* %__x) #4 align 2 {
entry:
  %__x.addr = alloca %"struct.std::_Rb_tree_node"*, align 8
  store %"struct.std::_Rb_tree_node"* %__x, %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  %0 = load %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  %_M_value_field = getelementptr inbounds %"struct.std::_Rb_tree_node"* %0, i32 0, i32 1
  ret %"struct.std::pair"* %_M_value_field
}

; Function Attrs: uwtable
define linkonce_odr %"struct.std::_Rb_tree_node"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE14_M_create_nodeERKS2_(%"class.std::_Rb_tree"* %this, %"struct.std::pair"* %__x) #2 align 2 {
entry:
  %this.addr = alloca %"class.std::_Rb_tree"*, align 8
  %__x.addr = alloca %"struct.std::pair"*, align 8
  %__tmp = alloca %"struct.std::_Rb_tree_node"*, align 8
  %temp.lvalue = alloca %"class.std::allocator.1", align 1
  %exn.slot = alloca i8*
  %ehselector.slot = alloca i32
  store %"class.std::_Rb_tree"* %this, %"class.std::_Rb_tree"** %this.addr, align 8
  store %"struct.std::pair"* %__x, %"struct.std::pair"** %__x.addr, align 8
  %this1 = load %"class.std::_Rb_tree"** %this.addr
  %call = call %"struct.std::_Rb_tree_node"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE11_M_get_nodeEv(%"class.std::_Rb_tree"* %this1)
  store %"struct.std::_Rb_tree_node"* %call, %"struct.std::_Rb_tree_node"** %__tmp, align 8
  invoke void @_ZNKSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE13get_allocatorEv(%"class.std::allocator.1"* sret %temp.lvalue, %"class.std::_Rb_tree"* %this1)
          to label %invoke.cont unwind label %lpad

invoke.cont:                                      ; preds = %entry
  %0 = bitcast %"class.std::allocator.1"* %temp.lvalue to %"class.__gnu_cxx::new_allocator.2"*
  %1 = load %"struct.std::_Rb_tree_node"** %__tmp, align 8
  %_M_value_field = getelementptr inbounds %"struct.std::_Rb_tree_node"* %1, i32 0, i32 1
  %call4 = invoke %"struct.std::pair"* @_ZSt11__addressofISt4pairIKiiEEPT_RS3_(%"struct.std::pair"* %_M_value_field)
          to label %invoke.cont3 unwind label %lpad2

invoke.cont3:                                     ; preds = %invoke.cont
  %2 = load %"struct.std::pair"** %__x.addr, align 8
  invoke void @_ZN9__gnu_cxx13new_allocatorISt4pairIKiiEE9constructEPS3_RKS3_(%"class.__gnu_cxx::new_allocator.2"* %0, %"struct.std::pair"* %call4, %"struct.std::pair"* %2)
          to label %invoke.cont5 unwind label %lpad2

invoke.cont5:                                     ; preds = %invoke.cont3
  call void @_ZNSaISt4pairIKiiEED2Ev(%"class.std::allocator.1"* %temp.lvalue) #1
  br label %try.cont

lpad:                                             ; preds = %entry
  %3 = landingpad { i8*, i32 } personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*)
          catch i8* null
  %4 = extractvalue { i8*, i32 } %3, 0
  store i8* %4, i8** %exn.slot
  %5 = extractvalue { i8*, i32 } %3, 1
  store i32 %5, i32* %ehselector.slot
  br label %catch

lpad2:                                            ; preds = %invoke.cont3, %invoke.cont
  %6 = landingpad { i8*, i32 } personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*)
          catch i8* null
  %7 = extractvalue { i8*, i32 } %6, 0
  store i8* %7, i8** %exn.slot
  %8 = extractvalue { i8*, i32 } %6, 1
  store i32 %8, i32* %ehselector.slot
  call void @_ZNSaISt4pairIKiiEED2Ev(%"class.std::allocator.1"* %temp.lvalue) #1
  br label %catch

catch:                                            ; preds = %lpad2, %lpad
  %exn = load i8** %exn.slot
  %9 = call i8* @__cxa_begin_catch(i8* %exn) #1
  %10 = load %"struct.std::_Rb_tree_node"** %__tmp, align 8
  invoke void @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE11_M_put_nodeEPSt13_Rb_tree_nodeIS2_E(%"class.std::_Rb_tree"* %this1, %"struct.std::_Rb_tree_node"* %10)
          to label %invoke.cont7 unwind label %lpad6

invoke.cont7:                                     ; preds = %catch
  invoke void @__cxa_rethrow() #13
          to label %unreachable unwind label %lpad6

lpad6:                                            ; preds = %invoke.cont7, %catch
  %11 = landingpad { i8*, i32 } personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*)
          cleanup
  %12 = extractvalue { i8*, i32 } %11, 0
  store i8* %12, i8** %exn.slot
  %13 = extractvalue { i8*, i32 } %11, 1
  store i32 %13, i32* %ehselector.slot
  invoke void @__cxa_end_catch()
          to label %invoke.cont8 unwind label %terminate.lpad

invoke.cont8:                                     ; preds = %lpad6
  br label %eh.resume

try.cont:                                         ; preds = %invoke.cont5
  %14 = load %"struct.std::_Rb_tree_node"** %__tmp, align 8
  ret %"struct.std::_Rb_tree_node"* %14

eh.resume:                                        ; preds = %invoke.cont8
  %exn9 = load i8** %exn.slot
  %sel = load i32* %ehselector.slot
  %lpad.val = insertvalue { i8*, i32 } undef, i8* %exn9, 0
  %lpad.val10 = insertvalue { i8*, i32 } %lpad.val, i32 %sel, 1
  resume { i8*, i32 } %lpad.val10

terminate.lpad:                                   ; preds = %lpad6
  %15 = landingpad { i8*, i32 } personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*)
          catch i8* null
  %16 = extractvalue { i8*, i32 } %15, 0
  call void @__clang_call_terminate(i8* %16) #14
  unreachable

unreachable:                                      ; preds = %invoke.cont7
  unreachable
}

; Function Attrs: nounwind
declare void @_ZSt29_Rb_tree_insert_and_rebalancebPSt18_Rb_tree_node_baseS0_RS_(i1 zeroext, %"struct.std::_Rb_tree_node_base"*, %"struct.std::_Rb_tree_node_base"*, %"struct.std::_Rb_tree_node_base"*) #6

; Function Attrs: uwtable
define linkonce_odr %"struct.std::_Rb_tree_node"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE11_M_get_nodeEv(%"class.std::_Rb_tree"* %this) #2 align 2 {
entry:
  %this.addr = alloca %"class.std::_Rb_tree"*, align 8
  store %"class.std::_Rb_tree"* %this, %"class.std::_Rb_tree"** %this.addr, align 8
  %this1 = load %"class.std::_Rb_tree"** %this.addr
  %_M_impl = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  %0 = bitcast %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl to %"class.std::allocator"*
  %1 = bitcast %"class.std::allocator"* %0 to %"class.__gnu_cxx::new_allocator"*
  %call = call %"struct.std::_Rb_tree_node"* @_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKiiEEE8allocateEmPKv(%"class.__gnu_cxx::new_allocator"* %1, i64 1, i8* null)
  ret %"struct.std::_Rb_tree_node"* %call
}

; Function Attrs: uwtable
define linkonce_odr void @_ZNKSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE13get_allocatorEv(%"class.std::allocator.1"* noalias sret %agg.result, %"class.std::_Rb_tree"* %this) #2 align 2 {
entry:
  %this.addr = alloca %"class.std::_Rb_tree"*, align 8
  store %"class.std::_Rb_tree"* %this, %"class.std::_Rb_tree"** %this.addr, align 8
  %this1 = load %"class.std::_Rb_tree"** %this.addr
  %call = call %"class.std::allocator"* @_ZNKSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE21_M_get_Node_allocatorEv(%"class.std::_Rb_tree"* %this1)
  call void @_ZNSaISt4pairIKiiEEC2ISt13_Rb_tree_nodeIS1_EEERKSaIT_E(%"class.std::allocator.1"* %agg.result, %"class.std::allocator"* %call) #1
  ret void
}

declare i32 @__gxx_personality_v0(...)

; Function Attrs: nounwind uwtable
define linkonce_odr void @_ZN9__gnu_cxx13new_allocatorISt4pairIKiiEE9constructEPS3_RKS3_(%"class.__gnu_cxx::new_allocator.2"* %this, %"struct.std::pair"* %__p, %"struct.std::pair"* %__val) #4 align 2 {
entry:
  %this.addr = alloca %"class.__gnu_cxx::new_allocator.2"*, align 8
  %__p.addr = alloca %"struct.std::pair"*, align 8
  %__val.addr = alloca %"struct.std::pair"*, align 8
  store %"class.__gnu_cxx::new_allocator.2"* %this, %"class.__gnu_cxx::new_allocator.2"** %this.addr, align 8
  store %"struct.std::pair"* %__p, %"struct.std::pair"** %__p.addr, align 8
  store %"struct.std::pair"* %__val, %"struct.std::pair"** %__val.addr, align 8
  %this1 = load %"class.__gnu_cxx::new_allocator.2"** %this.addr
  %0 = load %"struct.std::pair"** %__p.addr, align 8
  %1 = bitcast %"struct.std::pair"* %0 to i8*
  %new.isnull = icmp eq i8* %1, null
  br i1 %new.isnull, label %new.cont, label %new.notnull

new.notnull:                                      ; preds = %entry
  %2 = bitcast i8* %1 to %"struct.std::pair"*
  %3 = load %"struct.std::pair"** %__val.addr, align 8
  %4 = bitcast %"struct.std::pair"* %2 to i8*
  %5 = bitcast %"struct.std::pair"* %3 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %4, i8* %5, i64 8, i32 4, i1 false)
  br label %new.cont

new.cont:                                         ; preds = %new.notnull, %entry
  %6 = phi %"struct.std::pair"* [ %2, %new.notnull ], [ null, %entry ]
  ret void
}

; Function Attrs: inlinehint nounwind uwtable
define linkonce_odr %"struct.std::pair"* @_ZSt11__addressofISt4pairIKiiEEPT_RS3_(%"struct.std::pair"* %__r) #7 {
entry:
  %__r.addr = alloca %"struct.std::pair"*, align 8
  store %"struct.std::pair"* %__r, %"struct.std::pair"** %__r.addr, align 8
  %0 = load %"struct.std::pair"** %__r.addr, align 8
  %1 = bitcast %"struct.std::pair"* %0 to i8*
  %2 = bitcast i8* %1 to %"struct.std::pair"*
  ret %"struct.std::pair"* %2
}

; Function Attrs: nounwind uwtable
define linkonce_odr void @_ZNSaISt4pairIKiiEED2Ev(%"class.std::allocator.1"* %this) unnamed_addr #4 align 2 {
entry:
  %this.addr = alloca %"class.std::allocator.1"*, align 8
  store %"class.std::allocator.1"* %this, %"class.std::allocator.1"** %this.addr, align 8
  %this1 = load %"class.std::allocator.1"** %this.addr
  %0 = bitcast %"class.std::allocator.1"* %this1 to %"class.__gnu_cxx::new_allocator.2"*
  call void @_ZN9__gnu_cxx13new_allocatorISt4pairIKiiEED2Ev(%"class.__gnu_cxx::new_allocator.2"* %0) #1
  ret void
}

declare i8* @__cxa_begin_catch(i8*)

; Function Attrs: uwtable
define linkonce_odr void @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE11_M_put_nodeEPSt13_Rb_tree_nodeIS2_E(%"class.std::_Rb_tree"* %this, %"struct.std::_Rb_tree_node"* %__p) #2 align 2 {
entry:
  %this.addr = alloca %"class.std::_Rb_tree"*, align 8
  %__p.addr = alloca %"struct.std::_Rb_tree_node"*, align 8
  store %"class.std::_Rb_tree"* %this, %"class.std::_Rb_tree"** %this.addr, align 8
  store %"struct.std::_Rb_tree_node"* %__p, %"struct.std::_Rb_tree_node"** %__p.addr, align 8
  %this1 = load %"class.std::_Rb_tree"** %this.addr
  %_M_impl = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  %0 = bitcast %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl to %"class.std::allocator"*
  %1 = bitcast %"class.std::allocator"* %0 to %"class.__gnu_cxx::new_allocator"*
  %2 = load %"struct.std::_Rb_tree_node"** %__p.addr, align 8
  call void @_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKiiEEE10deallocateEPS5_m(%"class.__gnu_cxx::new_allocator"* %1, %"struct.std::_Rb_tree_node"* %2, i64 1)
  ret void
}

declare void @__cxa_rethrow()

declare void @__cxa_end_catch()

; Function Attrs: noinline noreturn nounwind
define linkonce_odr hidden void @__clang_call_terminate(i8*) #8 {
  %2 = call i8* @__cxa_begin_catch(i8* %0) #1
  call void @_ZSt9terminatev() #14
  unreachable
}

declare void @_ZSt9terminatev()

; Function Attrs: nounwind uwtable
define linkonce_odr void @_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKiiEEE10deallocateEPS5_m(%"class.__gnu_cxx::new_allocator"* %this, %"struct.std::_Rb_tree_node"* %__p, i64) #4 align 2 {
entry:
  %this.addr = alloca %"class.__gnu_cxx::new_allocator"*, align 8
  %__p.addr = alloca %"struct.std::_Rb_tree_node"*, align 8
  %.addr = alloca i64, align 8
  store %"class.__gnu_cxx::new_allocator"* %this, %"class.__gnu_cxx::new_allocator"** %this.addr, align 8
  store %"struct.std::_Rb_tree_node"* %__p, %"struct.std::_Rb_tree_node"** %__p.addr, align 8
  store i64 %0, i64* %.addr, align 8
  %this1 = load %"class.__gnu_cxx::new_allocator"** %this.addr
  %1 = load %"struct.std::_Rb_tree_node"** %__p.addr, align 8
  %2 = bitcast %"struct.std::_Rb_tree_node"* %1 to i8*
  call void @_ZdlPv(i8* %2) #1
  ret void
}

; Function Attrs: nobuiltin nounwind
declare void @_ZdlPv(i8*) #9

; Function Attrs: nounwind uwtable
define linkonce_odr void @_ZN9__gnu_cxx13new_allocatorISt4pairIKiiEED2Ev(%"class.__gnu_cxx::new_allocator.2"* %this) unnamed_addr #4 align 2 {
entry:
  %this.addr = alloca %"class.__gnu_cxx::new_allocator.2"*, align 8
  store %"class.__gnu_cxx::new_allocator.2"* %this, %"class.__gnu_cxx::new_allocator.2"** %this.addr, align 8
  %this1 = load %"class.__gnu_cxx::new_allocator.2"** %this.addr
  ret void
}

; Function Attrs: nounwind uwtable
define linkonce_odr void @_ZNSaISt4pairIKiiEEC2ISt13_Rb_tree_nodeIS1_EEERKSaIT_E(%"class.std::allocator.1"* %this, %"class.std::allocator"*) unnamed_addr #4 align 2 {
entry:
  %this.addr = alloca %"class.std::allocator.1"*, align 8
  %.addr = alloca %"class.std::allocator"*, align 8
  store %"class.std::allocator.1"* %this, %"class.std::allocator.1"** %this.addr, align 8
  store %"class.std::allocator"* %0, %"class.std::allocator"** %.addr, align 8
  %this1 = load %"class.std::allocator.1"** %this.addr
  %1 = bitcast %"class.std::allocator.1"* %this1 to %"class.__gnu_cxx::new_allocator.2"*
  call void @_ZN9__gnu_cxx13new_allocatorISt4pairIKiiEEC2Ev(%"class.__gnu_cxx::new_allocator.2"* %1) #1
  ret void
}

; Function Attrs: nounwind uwtable
define linkonce_odr %"class.std::allocator"* @_ZNKSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE21_M_get_Node_allocatorEv(%"class.std::_Rb_tree"* %this) #4 align 2 {
entry:
  %this.addr = alloca %"class.std::_Rb_tree"*, align 8
  store %"class.std::_Rb_tree"* %this, %"class.std::_Rb_tree"** %this.addr, align 8
  %this1 = load %"class.std::_Rb_tree"** %this.addr
  %_M_impl = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  %0 = bitcast %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl to %"class.std::allocator"*
  ret %"class.std::allocator"* %0
}

; Function Attrs: nounwind uwtable
define linkonce_odr void @_ZN9__gnu_cxx13new_allocatorISt4pairIKiiEEC2Ev(%"class.__gnu_cxx::new_allocator.2"* %this) unnamed_addr #4 align 2 {
entry:
  %this.addr = alloca %"class.__gnu_cxx::new_allocator.2"*, align 8
  store %"class.__gnu_cxx::new_allocator.2"* %this, %"class.__gnu_cxx::new_allocator.2"** %this.addr, align 8
  %this1 = load %"class.__gnu_cxx::new_allocator.2"** %this.addr
  ret void
}

; Function Attrs: uwtable
define linkonce_odr %"struct.std::_Rb_tree_node"* @_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKiiEEE8allocateEmPKv(%"class.__gnu_cxx::new_allocator"* %this, i64 %__n, i8*) #2 align 2 {
entry:
  %this.addr = alloca %"class.__gnu_cxx::new_allocator"*, align 8
  %__n.addr = alloca i64, align 8
  %.addr = alloca i8*, align 8
  store %"class.__gnu_cxx::new_allocator"* %this, %"class.__gnu_cxx::new_allocator"** %this.addr, align 8
  store i64 %__n, i64* %__n.addr, align 8
  store i8* %0, i8** %.addr, align 8
  %this1 = load %"class.__gnu_cxx::new_allocator"** %this.addr
  %1 = load i64* %__n.addr, align 8
  %call = call i64 @_ZNK9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKiiEEE8max_sizeEv(%"class.__gnu_cxx::new_allocator"* %this1) #1
  %cmp = icmp ugt i64 %1, %call
  br i1 %cmp, label %if.then, label %if.end

if.then:                                          ; preds = %entry
  call void @_ZSt17__throw_bad_allocv() #13
  unreachable

if.end:                                           ; preds = %entry
  %2 = load i64* %__n.addr, align 8
  %mul = mul i64 %2, 40
  %call2 = call noalias i8* @_Znwm(i64 %mul)
  %3 = bitcast i8* %call2 to %"struct.std::_Rb_tree_node"*
  ret %"struct.std::_Rb_tree_node"* %3
}

; Function Attrs: nounwind uwtable
define linkonce_odr i64 @_ZNK9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKiiEEE8max_sizeEv(%"class.__gnu_cxx::new_allocator"* %this) #4 align 2 {
entry:
  %this.addr = alloca %"class.__gnu_cxx::new_allocator"*, align 8
  store %"class.__gnu_cxx::new_allocator"* %this, %"class.__gnu_cxx::new_allocator"** %this.addr, align 8
  %this1 = load %"class.__gnu_cxx::new_allocator"** %this.addr
  ret i64 461168601842738790
}

; Function Attrs: noreturn
declare void @_ZSt17__throw_bad_allocv() #10

; Function Attrs: nobuiltin
declare noalias i8* @_Znwm(i64) #11

; Function Attrs: nounwind uwtable
define linkonce_odr %"struct.std::pair"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE8_S_valueEPKSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %__x) #4 align 2 {
entry:
  %__x.addr = alloca %"struct.std::_Rb_tree_node_base"*, align 8
  store %"struct.std::_Rb_tree_node_base"* %__x, %"struct.std::_Rb_tree_node_base"** %__x.addr, align 8
  %0 = load %"struct.std::_Rb_tree_node_base"** %__x.addr, align 8
  %1 = bitcast %"struct.std::_Rb_tree_node_base"* %0 to %"struct.std::_Rb_tree_node"*
  %_M_value_field = getelementptr inbounds %"struct.std::_Rb_tree_node"* %1, i32 0, i32 1
  ret %"struct.std::pair"* %_M_value_field
}

; Function Attrs: nounwind uwtable
define linkonce_odr void @_ZNKSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE8key_compEv(%"class.std::_Rb_tree"* %this) #4 align 2 {
entry:
  %retval = alloca %"struct.std::less", align 1
  %this.addr = alloca %"class.std::_Rb_tree"*, align 8
  store %"class.std::_Rb_tree"* %this, %"class.std::_Rb_tree"** %this.addr, align 8
  %this1 = load %"class.std::_Rb_tree"** %this.addr
  %_M_impl = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  %_M_key_compare = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl, i32 0, i32 0
  ret void
}

; Function Attrs: uwtable
define linkonce_odr %"struct.std::_Rb_tree_node_base"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE3endEv(%"class.std::_Rb_tree"* %this) #2 align 2 {
entry:
  %retval = alloca %"struct.std::_Rb_tree_iterator", align 8
  %this.addr = alloca %"class.std::_Rb_tree"*, align 8
  store %"class.std::_Rb_tree"* %this, %"class.std::_Rb_tree"** %this.addr, align 8
  %this1 = load %"class.std::_Rb_tree"** %this.addr
  %_M_impl = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  %_M_header = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl, i32 0, i32 1
  %0 = bitcast %"struct.std::_Rb_tree_node_base"* %_M_header to %"struct.std::_Rb_tree_node"*
  call void @_ZNSt17_Rb_tree_iteratorISt4pairIKiiEEC2EPSt13_Rb_tree_nodeIS2_E(%"struct.std::_Rb_tree_iterator"* %retval, %"struct.std::_Rb_tree_node"* %0)
  %coerce.dive = getelementptr %"struct.std::_Rb_tree_iterator"* %retval, i32 0, i32 0
  %1 = load %"struct.std::_Rb_tree_node_base"** %coerce.dive
  ret %"struct.std::_Rb_tree_node_base"* %1
}

; Function Attrs: uwtable
define linkonce_odr %"struct.std::_Rb_tree_node_base"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE11lower_boundERS1_(%"class.std::_Rb_tree"* %this, i32* %__k) #2 align 2 {
entry:
  %retval = alloca %"struct.std::_Rb_tree_iterator", align 8
  %this.addr = alloca %"class.std::_Rb_tree"*, align 8
  %__k.addr = alloca i32*, align 8
  store %"class.std::_Rb_tree"* %this, %"class.std::_Rb_tree"** %this.addr, align 8
  store i32* %__k, i32** %__k.addr, align 8
  %this1 = load %"class.std::_Rb_tree"** %this.addr
  %call = call %"struct.std::_Rb_tree_node"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE8_M_beginEv(%"class.std::_Rb_tree"* %this1)
  %call2 = call %"struct.std::_Rb_tree_node"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE6_M_endEv(%"class.std::_Rb_tree"* %this1)
  %0 = load i32** %__k.addr, align 8
  %call3 = call %"struct.std::_Rb_tree_node_base"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE14_M_lower_boundEPSt13_Rb_tree_nodeIS2_ESB_RS1_(%"class.std::_Rb_tree"* %this1, %"struct.std::_Rb_tree_node"* %call, %"struct.std::_Rb_tree_node"* %call2, i32* %0)
  %coerce.dive = getelementptr %"struct.std::_Rb_tree_iterator"* %retval, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %call3, %"struct.std::_Rb_tree_node_base"** %coerce.dive
  %coerce.dive4 = getelementptr %"struct.std::_Rb_tree_iterator"* %retval, i32 0, i32 0
  %1 = load %"struct.std::_Rb_tree_node_base"** %coerce.dive4
  ret %"struct.std::_Rb_tree_node_base"* %1
}

; Function Attrs: uwtable
define linkonce_odr %"struct.std::_Rb_tree_node_base"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE14_M_lower_boundEPSt13_Rb_tree_nodeIS2_ESB_RS1_(%"class.std::_Rb_tree"* %this, %"struct.std::_Rb_tree_node"* %__x, %"struct.std::_Rb_tree_node"* %__y, i32* %__k) #2 align 2 {
entry:
  %retval = alloca %"struct.std::_Rb_tree_iterator", align 8
  %this.addr = alloca %"class.std::_Rb_tree"*, align 8
  %__x.addr = alloca %"struct.std::_Rb_tree_node"*, align 8
  %__y.addr = alloca %"struct.std::_Rb_tree_node"*, align 8
  %__k.addr = alloca i32*, align 8
  store %"class.std::_Rb_tree"* %this, %"class.std::_Rb_tree"** %this.addr, align 8
  store %"struct.std::_Rb_tree_node"* %__x, %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  store %"struct.std::_Rb_tree_node"* %__y, %"struct.std::_Rb_tree_node"** %__y.addr, align 8
  store i32* %__k, i32** %__k.addr, align 8
  %this1 = load %"class.std::_Rb_tree"** %this.addr
  br label %while.cond

while.cond:                                       ; preds = %if.end, %entry
  %0 = load %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  %cmp = icmp ne %"struct.std::_Rb_tree_node"* %0, null
  br i1 %cmp, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %_M_impl = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  %_M_key_compare = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl, i32 0, i32 0
  %1 = load %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  %call = call i32* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE6_S_keyEPKSt13_Rb_tree_nodeIS2_E(%"struct.std::_Rb_tree_node"* %1)
  %2 = load i32** %__k.addr, align 8
  %call2 = call zeroext i1 @_ZNKSt4lessIiEclERKiS2_(%"struct.std::less"* %_M_key_compare, i32* %call, i32* %2)
  br i1 %call2, label %if.else, label %if.then

if.then:                                          ; preds = %while.body
  %3 = load %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  store %"struct.std::_Rb_tree_node"* %3, %"struct.std::_Rb_tree_node"** %__y.addr, align 8
  %4 = load %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  %5 = bitcast %"struct.std::_Rb_tree_node"* %4 to %"struct.std::_Rb_tree_node_base"*
  %call3 = call %"struct.std::_Rb_tree_node"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE7_S_leftEPSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %5)
  store %"struct.std::_Rb_tree_node"* %call3, %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  br label %if.end

if.else:                                          ; preds = %while.body
  %6 = load %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  %7 = bitcast %"struct.std::_Rb_tree_node"* %6 to %"struct.std::_Rb_tree_node_base"*
  %call4 = call %"struct.std::_Rb_tree_node"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE8_S_rightEPSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %7)
  store %"struct.std::_Rb_tree_node"* %call4, %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %8 = load %"struct.std::_Rb_tree_node"** %__y.addr, align 8
  call void @_ZNSt17_Rb_tree_iteratorISt4pairIKiiEEC2EPSt13_Rb_tree_nodeIS2_E(%"struct.std::_Rb_tree_iterator"* %retval, %"struct.std::_Rb_tree_node"* %8)
  %coerce.dive = getelementptr %"struct.std::_Rb_tree_iterator"* %retval, i32 0, i32 0
  %9 = load %"struct.std::_Rb_tree_node_base"** %coerce.dive
  ret %"struct.std::_Rb_tree_node_base"* %9
}

; Function Attrs: uwtable
define linkonce_odr %"struct.std::_Rb_tree_node_base"* @_ZNKSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE4findERS1_(%"class.std::_Rb_tree"* %this, i32* %__k) #2 align 2 {
entry:
  %retval = alloca %"struct.std::_Rb_tree_const_iterator", align 8
  %this.addr = alloca %"class.std::_Rb_tree"*, align 8
  %__k.addr = alloca i32*, align 8
  %__j = alloca %"struct.std::_Rb_tree_const_iterator", align 8
  %ref.tmp = alloca %"struct.std::_Rb_tree_const_iterator", align 8
  store %"class.std::_Rb_tree"* %this, %"class.std::_Rb_tree"** %this.addr, align 8
  store i32* %__k, i32** %__k.addr, align 8
  %this1 = load %"class.std::_Rb_tree"** %this.addr
  %call = call %"struct.std::_Rb_tree_node"* @_ZNKSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE8_M_beginEv(%"class.std::_Rb_tree"* %this1)
  %call2 = call %"struct.std::_Rb_tree_node"* @_ZNKSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE6_M_endEv(%"class.std::_Rb_tree"* %this1)
  %0 = load i32** %__k.addr, align 8
  %call3 = call %"struct.std::_Rb_tree_node_base"* @_ZNKSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE14_M_lower_boundEPKSt13_Rb_tree_nodeIS2_ESC_RS1_(%"class.std::_Rb_tree"* %this1, %"struct.std::_Rb_tree_node"* %call, %"struct.std::_Rb_tree_node"* %call2, i32* %0)
  %coerce.dive = getelementptr %"struct.std::_Rb_tree_const_iterator"* %__j, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %call3, %"struct.std::_Rb_tree_node_base"** %coerce.dive
  %call4 = call %"struct.std::_Rb_tree_node_base"* @_ZNKSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE3endEv(%"class.std::_Rb_tree"* %this1)
  %coerce.dive5 = getelementptr %"struct.std::_Rb_tree_const_iterator"* %ref.tmp, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %call4, %"struct.std::_Rb_tree_node_base"** %coerce.dive5
  %call6 = call zeroext i1 @_ZNKSt23_Rb_tree_const_iteratorISt4pairIKiiEEeqERKS3_(%"struct.std::_Rb_tree_const_iterator"* %__j, %"struct.std::_Rb_tree_const_iterator"* %ref.tmp)
  br i1 %call6, label %cond.true, label %lor.lhs.false

lor.lhs.false:                                    ; preds = %entry
  %_M_impl = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  %_M_key_compare = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl, i32 0, i32 0
  %1 = load i32** %__k.addr, align 8
  %_M_node = getelementptr inbounds %"struct.std::_Rb_tree_const_iterator"* %__j, i32 0, i32 0
  %2 = load %"struct.std::_Rb_tree_node_base"** %_M_node, align 8
  %call7 = call i32* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE6_S_keyEPKSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %2)
  %call8 = call zeroext i1 @_ZNKSt4lessIiEclERKiS2_(%"struct.std::less"* %_M_key_compare, i32* %1, i32* %call7)
  br i1 %call8, label %cond.true, label %cond.false

cond.true:                                        ; preds = %lor.lhs.false, %entry
  %call9 = call %"struct.std::_Rb_tree_node_base"* @_ZNKSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE3endEv(%"class.std::_Rb_tree"* %this1)
  %coerce.dive10 = getelementptr %"struct.std::_Rb_tree_const_iterator"* %retval, i32 0, i32 0
  store %"struct.std::_Rb_tree_node_base"* %call9, %"struct.std::_Rb_tree_node_base"** %coerce.dive10
  br label %cond.end

cond.false:                                       ; preds = %lor.lhs.false
  %3 = bitcast %"struct.std::_Rb_tree_const_iterator"* %retval to i8*
  %4 = bitcast %"struct.std::_Rb_tree_const_iterator"* %__j to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %3, i8* %4, i64 8, i32 8, i1 false)
  br label %cond.end

cond.end:                                         ; preds = %cond.false, %cond.true
  %coerce.dive11 = getelementptr %"struct.std::_Rb_tree_const_iterator"* %retval, i32 0, i32 0
  %5 = load %"struct.std::_Rb_tree_node_base"** %coerce.dive11
  ret %"struct.std::_Rb_tree_node_base"* %5
}

; Function Attrs: nounwind uwtable
define linkonce_odr zeroext i1 @_ZNKSt23_Rb_tree_const_iteratorISt4pairIKiiEEeqERKS3_(%"struct.std::_Rb_tree_const_iterator"* %this, %"struct.std::_Rb_tree_const_iterator"* %__x) #4 align 2 {
entry:
  %this.addr = alloca %"struct.std::_Rb_tree_const_iterator"*, align 8
  %__x.addr = alloca %"struct.std::_Rb_tree_const_iterator"*, align 8
  store %"struct.std::_Rb_tree_const_iterator"* %this, %"struct.std::_Rb_tree_const_iterator"** %this.addr, align 8
  store %"struct.std::_Rb_tree_const_iterator"* %__x, %"struct.std::_Rb_tree_const_iterator"** %__x.addr, align 8
  %this1 = load %"struct.std::_Rb_tree_const_iterator"** %this.addr
  %_M_node = getelementptr inbounds %"struct.std::_Rb_tree_const_iterator"* %this1, i32 0, i32 0
  %0 = load %"struct.std::_Rb_tree_node_base"** %_M_node, align 8
  %1 = load %"struct.std::_Rb_tree_const_iterator"** %__x.addr, align 8
  %_M_node2 = getelementptr inbounds %"struct.std::_Rb_tree_const_iterator"* %1, i32 0, i32 0
  %2 = load %"struct.std::_Rb_tree_node_base"** %_M_node2, align 8
  %cmp = icmp eq %"struct.std::_Rb_tree_node_base"* %0, %2
  ret i1 %cmp
}

; Function Attrs: uwtable
define linkonce_odr %"struct.std::_Rb_tree_node_base"* @_ZNKSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE3endEv(%"class.std::_Rb_tree"* %this) #2 align 2 {
entry:
  %retval = alloca %"struct.std::_Rb_tree_const_iterator", align 8
  %this.addr = alloca %"class.std::_Rb_tree"*, align 8
  store %"class.std::_Rb_tree"* %this, %"class.std::_Rb_tree"** %this.addr, align 8
  %this1 = load %"class.std::_Rb_tree"** %this.addr
  %_M_impl = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  %_M_header = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl, i32 0, i32 1
  %0 = bitcast %"struct.std::_Rb_tree_node_base"* %_M_header to %"struct.std::_Rb_tree_node"*
  call void @_ZNSt23_Rb_tree_const_iteratorISt4pairIKiiEEC2EPKSt13_Rb_tree_nodeIS2_E(%"struct.std::_Rb_tree_const_iterator"* %retval, %"struct.std::_Rb_tree_node"* %0)
  %coerce.dive = getelementptr %"struct.std::_Rb_tree_const_iterator"* %retval, i32 0, i32 0
  %1 = load %"struct.std::_Rb_tree_node_base"** %coerce.dive
  ret %"struct.std::_Rb_tree_node_base"* %1
}

; Function Attrs: nounwind uwtable
define linkonce_odr void @_ZNSt23_Rb_tree_const_iteratorISt4pairIKiiEEC2EPKSt13_Rb_tree_nodeIS2_E(%"struct.std::_Rb_tree_const_iterator"* %this, %"struct.std::_Rb_tree_node"* %__x) unnamed_addr #4 align 2 {
entry:
  %this.addr = alloca %"struct.std::_Rb_tree_const_iterator"*, align 8
  %__x.addr = alloca %"struct.std::_Rb_tree_node"*, align 8
  store %"struct.std::_Rb_tree_const_iterator"* %this, %"struct.std::_Rb_tree_const_iterator"** %this.addr, align 8
  store %"struct.std::_Rb_tree_node"* %__x, %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  %this1 = load %"struct.std::_Rb_tree_const_iterator"** %this.addr
  %_M_node = getelementptr inbounds %"struct.std::_Rb_tree_const_iterator"* %this1, i32 0, i32 0
  %0 = load %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  %1 = bitcast %"struct.std::_Rb_tree_node"* %0 to %"struct.std::_Rb_tree_node_base"*
  store %"struct.std::_Rb_tree_node_base"* %1, %"struct.std::_Rb_tree_node_base"** %_M_node, align 8
  ret void
}

; Function Attrs: uwtable
define linkonce_odr %"struct.std::_Rb_tree_node_base"* @_ZNKSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE14_M_lower_boundEPKSt13_Rb_tree_nodeIS2_ESC_RS1_(%"class.std::_Rb_tree"* %this, %"struct.std::_Rb_tree_node"* %__x, %"struct.std::_Rb_tree_node"* %__y, i32* %__k) #2 align 2 {
entry:
  %retval = alloca %"struct.std::_Rb_tree_const_iterator", align 8
  %this.addr = alloca %"class.std::_Rb_tree"*, align 8
  %__x.addr = alloca %"struct.std::_Rb_tree_node"*, align 8
  %__y.addr = alloca %"struct.std::_Rb_tree_node"*, align 8
  %__k.addr = alloca i32*, align 8
  store %"class.std::_Rb_tree"* %this, %"class.std::_Rb_tree"** %this.addr, align 8
  store %"struct.std::_Rb_tree_node"* %__x, %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  store %"struct.std::_Rb_tree_node"* %__y, %"struct.std::_Rb_tree_node"** %__y.addr, align 8
  store i32* %__k, i32** %__k.addr, align 8
  %this1 = load %"class.std::_Rb_tree"** %this.addr
  br label %while.cond

while.cond:                                       ; preds = %if.end, %entry
  %0 = load %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  %cmp = icmp ne %"struct.std::_Rb_tree_node"* %0, null
  br i1 %cmp, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %_M_impl = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  %_M_key_compare = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl, i32 0, i32 0
  %1 = load %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  %call = call i32* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE6_S_keyEPKSt13_Rb_tree_nodeIS2_E(%"struct.std::_Rb_tree_node"* %1)
  %2 = load i32** %__k.addr, align 8
  %call2 = call zeroext i1 @_ZNKSt4lessIiEclERKiS2_(%"struct.std::less"* %_M_key_compare, i32* %call, i32* %2)
  br i1 %call2, label %if.else, label %if.then

if.then:                                          ; preds = %while.body
  %3 = load %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  store %"struct.std::_Rb_tree_node"* %3, %"struct.std::_Rb_tree_node"** %__y.addr, align 8
  %4 = load %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  %5 = bitcast %"struct.std::_Rb_tree_node"* %4 to %"struct.std::_Rb_tree_node_base"*
  %call3 = call %"struct.std::_Rb_tree_node"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE7_S_leftEPKSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %5)
  store %"struct.std::_Rb_tree_node"* %call3, %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  br label %if.end

if.else:                                          ; preds = %while.body
  %6 = load %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  %7 = bitcast %"struct.std::_Rb_tree_node"* %6 to %"struct.std::_Rb_tree_node_base"*
  %call4 = call %"struct.std::_Rb_tree_node"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE8_S_rightEPKSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %7)
  store %"struct.std::_Rb_tree_node"* %call4, %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  br label %if.end

if.end:                                           ; preds = %if.else, %if.then
  br label %while.cond

while.end:                                        ; preds = %while.cond
  %8 = load %"struct.std::_Rb_tree_node"** %__y.addr, align 8
  call void @_ZNSt23_Rb_tree_const_iteratorISt4pairIKiiEEC2EPKSt13_Rb_tree_nodeIS2_E(%"struct.std::_Rb_tree_const_iterator"* %retval, %"struct.std::_Rb_tree_node"* %8)
  %coerce.dive = getelementptr %"struct.std::_Rb_tree_const_iterator"* %retval, i32 0, i32 0
  %9 = load %"struct.std::_Rb_tree_node_base"** %coerce.dive
  ret %"struct.std::_Rb_tree_node_base"* %9
}

; Function Attrs: nounwind uwtable
define linkonce_odr %"struct.std::_Rb_tree_node"* @_ZNKSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE8_M_beginEv(%"class.std::_Rb_tree"* %this) #4 align 2 {
entry:
  %this.addr = alloca %"class.std::_Rb_tree"*, align 8
  store %"class.std::_Rb_tree"* %this, %"class.std::_Rb_tree"** %this.addr, align 8
  %this1 = load %"class.std::_Rb_tree"** %this.addr
  %_M_impl = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  %_M_header = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl, i32 0, i32 1
  %_M_parent = getelementptr inbounds %"struct.std::_Rb_tree_node_base"* %_M_header, i32 0, i32 1
  %0 = load %"struct.std::_Rb_tree_node_base"** %_M_parent, align 8
  %1 = bitcast %"struct.std::_Rb_tree_node_base"* %0 to %"struct.std::_Rb_tree_node"*
  ret %"struct.std::_Rb_tree_node"* %1
}

; Function Attrs: nounwind uwtable
define linkonce_odr %"struct.std::_Rb_tree_node"* @_ZNKSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE6_M_endEv(%"class.std::_Rb_tree"* %this) #4 align 2 {
entry:
  %this.addr = alloca %"class.std::_Rb_tree"*, align 8
  store %"class.std::_Rb_tree"* %this, %"class.std::_Rb_tree"** %this.addr, align 8
  %this1 = load %"class.std::_Rb_tree"** %this.addr
  %_M_impl = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  %_M_header = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl, i32 0, i32 1
  %0 = bitcast %"struct.std::_Rb_tree_node_base"* %_M_header to %"struct.std::_Rb_tree_node"*
  ret %"struct.std::_Rb_tree_node"* %0
}

; Function Attrs: nounwind uwtable
define linkonce_odr %"struct.std::_Rb_tree_node"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE7_S_leftEPKSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %__x) #4 align 2 {
entry:
  %__x.addr = alloca %"struct.std::_Rb_tree_node_base"*, align 8
  store %"struct.std::_Rb_tree_node_base"* %__x, %"struct.std::_Rb_tree_node_base"** %__x.addr, align 8
  %0 = load %"struct.std::_Rb_tree_node_base"** %__x.addr, align 8
  %_M_left = getelementptr inbounds %"struct.std::_Rb_tree_node_base"* %0, i32 0, i32 2
  %1 = load %"struct.std::_Rb_tree_node_base"** %_M_left, align 8
  %2 = bitcast %"struct.std::_Rb_tree_node_base"* %1 to %"struct.std::_Rb_tree_node"*
  ret %"struct.std::_Rb_tree_node"* %2
}

; Function Attrs: uwtable
define linkonce_odr void @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EEC2Ev(%"class.std::_Rb_tree"* %this) unnamed_addr #2 align 2 {
entry:
  %this.addr = alloca %"class.std::_Rb_tree"*, align 8
  store %"class.std::_Rb_tree"* %this, %"class.std::_Rb_tree"** %this.addr, align 8
  %this1 = load %"class.std::_Rb_tree"** %this.addr
  %_M_impl = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  call void @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE13_Rb_tree_implIS6_Lb0EEC2Ev(%"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl)
  ret void
}

; Function Attrs: uwtable
define linkonce_odr void @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE13_Rb_tree_implIS6_Lb0EEC2Ev(%"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %this) unnamed_addr #2 align 2 {
entry:
  %this.addr = alloca %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"*, align 8
  %exn.slot = alloca i8*
  %ehselector.slot = alloca i32
  store %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %this, %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"** %this.addr, align 8
  %this1 = load %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"** %this.addr
  %0 = bitcast %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %this1 to %"class.std::allocator"*
  call void @_ZNSaISt13_Rb_tree_nodeISt4pairIKiiEEEC2Ev(%"class.std::allocator"* %0) #1
  %_M_key_compare = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %this1, i32 0, i32 0
  %_M_header = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %this1, i32 0, i32 1
  %1 = bitcast %"struct.std::_Rb_tree_node_base"* %_M_header to i8*
  call void @llvm.memset.p0i8.i64(i8* %1, i8 0, i64 32, i32 8, i1 false)
  %_M_node_count = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %this1, i32 0, i32 2
  store i64 0, i64* %_M_node_count, align 8
  invoke void @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE13_Rb_tree_implIS6_Lb0EE13_M_initializeEv(%"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %this1)
          to label %invoke.cont unwind label %lpad

invoke.cont:                                      ; preds = %entry
  ret void

lpad:                                             ; preds = %entry
  %2 = landingpad { i8*, i32 } personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*)
          cleanup
  %3 = extractvalue { i8*, i32 } %2, 0
  store i8* %3, i8** %exn.slot
  %4 = extractvalue { i8*, i32 } %2, 1
  store i32 %4, i32* %ehselector.slot
  %5 = bitcast %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %this1 to %"class.std::allocator"*
  call void @_ZNSaISt13_Rb_tree_nodeISt4pairIKiiEEED2Ev(%"class.std::allocator"* %5) #1
  br label %eh.resume

eh.resume:                                        ; preds = %lpad
  %exn = load i8** %exn.slot
  %sel = load i32* %ehselector.slot
  %lpad.val = insertvalue { i8*, i32 } undef, i8* %exn, 0
  %lpad.val2 = insertvalue { i8*, i32 } %lpad.val, i32 %sel, 1
  resume { i8*, i32 } %lpad.val2
}

; Function Attrs: nounwind uwtable
define linkonce_odr void @_ZNSaISt13_Rb_tree_nodeISt4pairIKiiEEEC2Ev(%"class.std::allocator"* %this) unnamed_addr #4 align 2 {
entry:
  %this.addr = alloca %"class.std::allocator"*, align 8
  store %"class.std::allocator"* %this, %"class.std::allocator"** %this.addr, align 8
  %this1 = load %"class.std::allocator"** %this.addr
  %0 = bitcast %"class.std::allocator"* %this1 to %"class.__gnu_cxx::new_allocator"*
  call void @_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKiiEEEC2Ev(%"class.__gnu_cxx::new_allocator"* %0) #1
  ret void
}

; Function Attrs: nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture, i8, i64, i32, i1) #1

; Function Attrs: nounwind uwtable
define linkonce_odr void @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE13_Rb_tree_implIS6_Lb0EE13_M_initializeEv(%"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %this) #4 align 2 {
entry:
  %this.addr = alloca %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"*, align 8
  store %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %this, %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"** %this.addr, align 8
  %this1 = load %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"** %this.addr
  %_M_header = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %this1, i32 0, i32 1
  %_M_color = getelementptr inbounds %"struct.std::_Rb_tree_node_base"* %_M_header, i32 0, i32 0
  store i32 0, i32* %_M_color, align 4
  %_M_header2 = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %this1, i32 0, i32 1
  %_M_parent = getelementptr inbounds %"struct.std::_Rb_tree_node_base"* %_M_header2, i32 0, i32 1
  store %"struct.std::_Rb_tree_node_base"* null, %"struct.std::_Rb_tree_node_base"** %_M_parent, align 8
  %_M_header3 = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %this1, i32 0, i32 1
  %_M_header4 = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %this1, i32 0, i32 1
  %_M_left = getelementptr inbounds %"struct.std::_Rb_tree_node_base"* %_M_header4, i32 0, i32 2
  store %"struct.std::_Rb_tree_node_base"* %_M_header3, %"struct.std::_Rb_tree_node_base"** %_M_left, align 8
  %_M_header5 = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %this1, i32 0, i32 1
  %_M_header6 = getelementptr inbounds %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %this1, i32 0, i32 1
  %_M_right = getelementptr inbounds %"struct.std::_Rb_tree_node_base"* %_M_header6, i32 0, i32 3
  store %"struct.std::_Rb_tree_node_base"* %_M_header5, %"struct.std::_Rb_tree_node_base"** %_M_right, align 8
  ret void
}

; Function Attrs: nounwind uwtable
define linkonce_odr void @_ZNSaISt13_Rb_tree_nodeISt4pairIKiiEEED2Ev(%"class.std::allocator"* %this) unnamed_addr #4 align 2 {
entry:
  %this.addr = alloca %"class.std::allocator"*, align 8
  store %"class.std::allocator"* %this, %"class.std::allocator"** %this.addr, align 8
  %this1 = load %"class.std::allocator"** %this.addr
  %0 = bitcast %"class.std::allocator"* %this1 to %"class.__gnu_cxx::new_allocator"*
  call void @_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKiiEEED2Ev(%"class.__gnu_cxx::new_allocator"* %0) #1
  ret void
}

; Function Attrs: nounwind uwtable
define linkonce_odr void @_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKiiEEED2Ev(%"class.__gnu_cxx::new_allocator"* %this) unnamed_addr #4 align 2 {
entry:
  %this.addr = alloca %"class.__gnu_cxx::new_allocator"*, align 8
  store %"class.__gnu_cxx::new_allocator"* %this, %"class.__gnu_cxx::new_allocator"** %this.addr, align 8
  %this1 = load %"class.__gnu_cxx::new_allocator"** %this.addr
  ret void
}

; Function Attrs: nounwind uwtable
define linkonce_odr void @_ZN9__gnu_cxx13new_allocatorISt13_Rb_tree_nodeISt4pairIKiiEEEC2Ev(%"class.__gnu_cxx::new_allocator"* %this) unnamed_addr #4 align 2 {
entry:
  %this.addr = alloca %"class.__gnu_cxx::new_allocator"*, align 8
  store %"class.__gnu_cxx::new_allocator"* %this, %"class.__gnu_cxx::new_allocator"** %this.addr, align 8
  %this1 = load %"class.__gnu_cxx::new_allocator"** %this.addr
  ret void
}

; Function Attrs: uwtable
define linkonce_odr void @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EED2Ev(%"class.std::_Rb_tree"* %this) unnamed_addr #2 align 2 {
entry:
  %this.addr = alloca %"class.std::_Rb_tree"*, align 8
  %exn.slot = alloca i8*
  %ehselector.slot = alloca i32
  store %"class.std::_Rb_tree"* %this, %"class.std::_Rb_tree"** %this.addr, align 8
  %this1 = load %"class.std::_Rb_tree"** %this.addr
  %call = invoke %"struct.std::_Rb_tree_node"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE8_M_beginEv(%"class.std::_Rb_tree"* %this1)
          to label %invoke.cont unwind label %lpad

invoke.cont:                                      ; preds = %entry
  invoke void @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE8_M_eraseEPSt13_Rb_tree_nodeIS2_E(%"class.std::_Rb_tree"* %this1, %"struct.std::_Rb_tree_node"* %call)
          to label %invoke.cont2 unwind label %lpad

invoke.cont2:                                     ; preds = %invoke.cont
  %_M_impl = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  call void @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE13_Rb_tree_implIS6_Lb0EED2Ev(%"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl) #1
  ret void

lpad:                                             ; preds = %invoke.cont, %entry
  %0 = landingpad { i8*, i32 } personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*)
          cleanup
  %1 = extractvalue { i8*, i32 } %0, 0
  store i8* %1, i8** %exn.slot
  %2 = extractvalue { i8*, i32 } %0, 1
  store i32 %2, i32* %ehselector.slot
  %_M_impl3 = getelementptr inbounds %"class.std::_Rb_tree"* %this1, i32 0, i32 0
  call void @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE13_Rb_tree_implIS6_Lb0EED2Ev(%"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %_M_impl3) #1
  br label %eh.resume

eh.resume:                                        ; preds = %lpad
  %exn = load i8** %exn.slot
  %sel = load i32* %ehselector.slot
  %lpad.val = insertvalue { i8*, i32 } undef, i8* %exn, 0
  %lpad.val4 = insertvalue { i8*, i32 } %lpad.val, i32 %sel, 1
  resume { i8*, i32 } %lpad.val4
}

; Function Attrs: uwtable
define linkonce_odr void @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE8_M_eraseEPSt13_Rb_tree_nodeIS2_E(%"class.std::_Rb_tree"* %this, %"struct.std::_Rb_tree_node"* %__x) #2 align 2 {
entry:
  %this.addr = alloca %"class.std::_Rb_tree"*, align 8
  %__x.addr = alloca %"struct.std::_Rb_tree_node"*, align 8
  %__y = alloca %"struct.std::_Rb_tree_node"*, align 8
  store %"class.std::_Rb_tree"* %this, %"class.std::_Rb_tree"** %this.addr, align 8
  store %"struct.std::_Rb_tree_node"* %__x, %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  %this1 = load %"class.std::_Rb_tree"** %this.addr
  br label %while.cond

while.cond:                                       ; preds = %while.body, %entry
  %0 = load %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  %cmp = icmp ne %"struct.std::_Rb_tree_node"* %0, null
  br i1 %cmp, label %while.body, label %while.end

while.body:                                       ; preds = %while.cond
  %1 = load %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  %2 = bitcast %"struct.std::_Rb_tree_node"* %1 to %"struct.std::_Rb_tree_node_base"*
  %call = call %"struct.std::_Rb_tree_node"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE8_S_rightEPSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %2)
  call void @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE8_M_eraseEPSt13_Rb_tree_nodeIS2_E(%"class.std::_Rb_tree"* %this1, %"struct.std::_Rb_tree_node"* %call)
  %3 = load %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  %4 = bitcast %"struct.std::_Rb_tree_node"* %3 to %"struct.std::_Rb_tree_node_base"*
  %call2 = call %"struct.std::_Rb_tree_node"* @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE7_S_leftEPSt18_Rb_tree_node_base(%"struct.std::_Rb_tree_node_base"* %4)
  store %"struct.std::_Rb_tree_node"* %call2, %"struct.std::_Rb_tree_node"** %__y, align 8
  %5 = load %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  call void @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE15_M_destroy_nodeEPSt13_Rb_tree_nodeIS2_E(%"class.std::_Rb_tree"* %this1, %"struct.std::_Rb_tree_node"* %5)
  %6 = load %"struct.std::_Rb_tree_node"** %__y, align 8
  store %"struct.std::_Rb_tree_node"* %6, %"struct.std::_Rb_tree_node"** %__x.addr, align 8
  br label %while.cond

while.end:                                        ; preds = %while.cond
  ret void
}

; Function Attrs: inlinehint nounwind uwtable
define linkonce_odr void @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE13_Rb_tree_implIS6_Lb0EED2Ev(%"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %this) unnamed_addr #7 align 2 {
entry:
  %this.addr = alloca %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"*, align 8
  store %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %this, %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"** %this.addr, align 8
  %this1 = load %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"** %this.addr
  %0 = bitcast %"struct.std::_Rb_tree<int, std::pair<const int, int>, std::_Select1st<std::pair<const int, int> >, std::less<int>, std::allocator<std::pair<const int, int> > >::_Rb_tree_impl"* %this1 to %"class.std::allocator"*
  call void @_ZNSaISt13_Rb_tree_nodeISt4pairIKiiEEED2Ev(%"class.std::allocator"* %0) #1
  ret void
}

; Function Attrs: uwtable
define linkonce_odr void @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE15_M_destroy_nodeEPSt13_Rb_tree_nodeIS2_E(%"class.std::_Rb_tree"* %this, %"struct.std::_Rb_tree_node"* %__p) #2 align 2 {
entry:
  %this.addr = alloca %"class.std::_Rb_tree"*, align 8
  %__p.addr = alloca %"struct.std::_Rb_tree_node"*, align 8
  %temp.lvalue = alloca %"class.std::allocator.1", align 1
  %exn.slot = alloca i8*
  %ehselector.slot = alloca i32
  store %"class.std::_Rb_tree"* %this, %"class.std::_Rb_tree"** %this.addr, align 8
  store %"struct.std::_Rb_tree_node"* %__p, %"struct.std::_Rb_tree_node"** %__p.addr, align 8
  %this1 = load %"class.std::_Rb_tree"** %this.addr
  call void @_ZNKSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE13get_allocatorEv(%"class.std::allocator.1"* sret %temp.lvalue, %"class.std::_Rb_tree"* %this1)
  %0 = bitcast %"class.std::allocator.1"* %temp.lvalue to %"class.__gnu_cxx::new_allocator.2"*
  %1 = load %"struct.std::_Rb_tree_node"** %__p.addr, align 8
  %_M_value_field = getelementptr inbounds %"struct.std::_Rb_tree_node"* %1, i32 0, i32 1
  %call = invoke %"struct.std::pair"* @_ZSt11__addressofISt4pairIKiiEEPT_RS3_(%"struct.std::pair"* %_M_value_field)
          to label %invoke.cont unwind label %lpad

invoke.cont:                                      ; preds = %entry
  invoke void @_ZN9__gnu_cxx13new_allocatorISt4pairIKiiEE7destroyEPS3_(%"class.__gnu_cxx::new_allocator.2"* %0, %"struct.std::pair"* %call)
          to label %invoke.cont2 unwind label %lpad

invoke.cont2:                                     ; preds = %invoke.cont
  call void @_ZNSaISt4pairIKiiEED2Ev(%"class.std::allocator.1"* %temp.lvalue) #1
  %2 = load %"struct.std::_Rb_tree_node"** %__p.addr, align 8
  call void @_ZNSt8_Rb_treeIiSt4pairIKiiESt10_Select1stIS2_ESt4lessIiESaIS2_EE11_M_put_nodeEPSt13_Rb_tree_nodeIS2_E(%"class.std::_Rb_tree"* %this1, %"struct.std::_Rb_tree_node"* %2)
  ret void

lpad:                                             ; preds = %invoke.cont, %entry
  %3 = landingpad { i8*, i32 } personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*)
          cleanup
  %4 = extractvalue { i8*, i32 } %3, 0
  store i8* %4, i8** %exn.slot
  %5 = extractvalue { i8*, i32 } %3, 1
  store i32 %5, i32* %ehselector.slot
  call void @_ZNSaISt4pairIKiiEED2Ev(%"class.std::allocator.1"* %temp.lvalue) #1
  br label %eh.resume

eh.resume:                                        ; preds = %lpad
  %exn = load i8** %exn.slot
  %sel = load i32* %ehselector.slot
  %lpad.val = insertvalue { i8*, i32 } undef, i8* %exn, 0
  %lpad.val3 = insertvalue { i8*, i32 } %lpad.val, i32 %sel, 1
  resume { i8*, i32 } %lpad.val3
}

; Function Attrs: nounwind uwtable
define linkonce_odr void @_ZN9__gnu_cxx13new_allocatorISt4pairIKiiEE7destroyEPS3_(%"class.__gnu_cxx::new_allocator.2"* %this, %"struct.std::pair"* %__p) #4 align 2 {
entry:
  %this.addr = alloca %"class.__gnu_cxx::new_allocator.2"*, align 8
  %__p.addr = alloca %"struct.std::pair"*, align 8
  store %"class.__gnu_cxx::new_allocator.2"* %this, %"class.__gnu_cxx::new_allocator.2"** %this.addr, align 8
  store %"struct.std::pair"* %__p, %"struct.std::pair"** %__p.addr, align 8
  %this1 = load %"class.__gnu_cxx::new_allocator.2"** %this.addr
  %0 = load %"struct.std::pair"** %__p.addr, align 8
  ret void
}

define internal void @_GLOBAL__I_a() section ".text.startup" {
entry:
  call void @__cxx_global_var_init()
  call void @__cxx_global_var_init1()
  ret void
}

attributes #0 = { "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind }
attributes #2 = { uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { inlinehint uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind readonly "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { inlinehint nounwind uwtable "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { noinline noreturn nounwind }
attributes #9 = { nobuiltin nounwind "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #10 = { noreturn "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #11 = { nobuiltin "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #12 = { nounwind readonly }
attributes #13 = { noreturn }
attributes #14 = { noreturn nounwind }

!llvm.ident = !{!0}

!0 = metadata !{metadata !"clang version 3.4 (tags/RELEASE_34/final)"}
