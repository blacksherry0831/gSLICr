#check_for_cxx11_compiler########
check_for_cxx11_compiler(CXX11_COMPILER_T)
IF(CXX11_COMPILER_T)
 message(STATUS "Checking for C++11 compiler - available")
ENDIF()
###############################################################################
C11_Config()
############≈‰÷√OPENCV#########################################################
ConfigOpenCv()
###############################################################################
ConfigMFC_2()
###############################################################################
ConfigCUDA()
###############################################################################
SET(DIR_SRCS   
		cuda_base.cu
		fuzzy.cu
	    HarrWaveletKernel.cu
	    SlicKernel.cu
		
		slicLab.cu
		slicLabInt.cu
		
		ColorSpace.cu
		
		CUDA_Code.cpp		
		CUDA_Code_LAB.cpp	
		CUDA_Code_LAB_Int.cpp			
		) 


CUDA_ADD_LIBRARY(cuda_Lib   STATIC    ${DIR_SRCS}  )



	