
class checksum
{
  private:
    unsigned short sum;
  public:
    unsigned short get_checksum(char *data, int length);
};

// Create a simple checksum for comparing files to the non GUI version. 
unsigned short checksum::get_checksum(char * data, int length)
{
  int counter;
  sum=0; // Will overflow to creat a checksum.
  for(counter = 0; counter < length; ++ counter)
    sum+=data[counter];
  return(sum);
} 
