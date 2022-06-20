int __declspec(naked)BootLoaderRobco_ASM()
{
	_asm
	{
		push ebp
		mov ebp, esp
		sub esp, __LOCAL_SIZE
		//mov ax, offset buff  ; Load address of buff
	/*	
     use 16;
	 org 7c00h;
	 in 18h;
	 rb 512-($-7c00h)-2;
	 db 55h,0aah;
		  */

	}
}