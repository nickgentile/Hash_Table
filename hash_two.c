int  hash_example_two (char *s,  int T) {

   /* The parameter s represents the symbol to be hashed and  */
   /* the parameter T represents the size of the hash table.  */
   /* The function returns the hash value for the symbol s.   */

   /* String s is assumed to be terminated with '\0'.         */
   /* It is also assumed that T is at least 2. The returned   */
   /* hash value is an integer in the range 0 to T-1.         */

   /* The function computes the hash value using bitwise      */
   /* operations (namely left shift and exclusive or).        */

   #define  SHIFT_AMOUNT   5

   int h = 0;     /* Will hold the hash value at the end. */

   /* The hash value is computed in the loop below. */

   for (;  *s != 0;  s++)
      h = (h << SHIFT_AMOUNT) ^ (*s) ^ h;

   /* If the resulting hash value is negative, change it  */
   /* to a positive value before taking the remainder     */
   /* modulo T.                                           */

   if (h < 0)
      h = -h;

   return  (h % T);  /* The returned hash value. */

} /* End of hash_example_two */
