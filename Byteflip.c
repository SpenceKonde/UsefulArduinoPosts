// Reverse the order of bits in a byte. 
// I.e. MSB is swapped with LSB, etc. 
unsigned char Bit_Reverse( unsigned char x ) 
{ 
   x = ((x >> 1) & 0x55) | ((x << 1) & 0xaa); 
   x = ((x >> 2) & 0x33) | ((x << 2) & 0xcc); 
   x = ((x >> 4) & 0x0f) | ((x << 4) & 0xf0); 
   return x;    
}


unsigned char bitswap (unsigned char x)
{
 byte result;

   asm("mov __tmp_reg__, %[in] \n\t"
     "lsl __tmp_reg__  \n\t"   /* shift out high bit to carry */
     "ror %[out] \n\t"  /* rotate carry __tmp_reg__to low bit (eventually) */
     "lsl __tmp_reg__  \n\t"   /* 2 */
     "ror %[out] \n\t"
     "lsl __tmp_reg__  \n\t"   /* 3 */
     "ror %[out] \n\t"
     "lsl __tmp_reg__  \n\t"   /* 4 */
     "ror %[out] \n\t"
     
     "lsl __tmp_reg__  \n\t"   /* 5 */
     "ror %[out] \n\t"
     "lsl __tmp_reg__  \n\t"   /* 6 */
     "ror %[out] \n\t"
     "lsl __tmp_reg__  \n\t"   /* 7 */
     "ror %[out] \n\t"
     "lsl __tmp_reg__  \n\t"   /* 8 */
     "ror %[out] \n\t"
     : [out] "=r" (result) : [in] "r" (x));
     return(result);
}
