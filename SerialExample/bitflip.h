#ifndef BITFLIP
#define BITFLIP

#include <iostream>
#include <ctime>
#include <map>
#include <sys/time.h>
#include <stdlib.h>

using namespace std;

class BitFlip {
 public:
  /*
  void randomFlip(int *);
  void randomFlip(char *);
  void randomFlip(double *);
  void flipDoubleBit(double *, int);
  void randomFlip(map <int *,long int> map);

  void PflipBit (char *, int);

  void printBit (char*);
  void printBit (int*);
  void printBit (double*);

  int getRand();
  */
  static inline int getRand() {
  /*
    gettimeofday(&tseed,NULL);
    srand(tseed.tv_usec);
  */
    srand (time(NULL));
    return rand();
  }

  // set ith bit of ch to 1

  static inline unsigned char setBit (unsigned char ch, int i)
  {
    unsigned mask = 1 << i;
    return mask | ch;
  }

  // set ith bit of *cp to 1

  static inline void PsetBit (char * cp, int i)
  {
    unsigned mask = 1 << i;
    * cp = mask | *cp;
  }

  // get ith bit of ch

  static inline unsigned char getBit (char ch, int i)
  {
    return (ch >> i) & 1;
  }

  static inline unsigned char getBit (int num, int i)
  {
    char *p=(char*)&num;
    for (int j=3;j>0;j--)
    {
      if (i>j*8-1)
      {
        p = (char*)&num + j;
        i = i - (j * 8 );
        break;
      }
    }
    return (*p >> i)&1;
  }

  static inline unsigned char getBit(double dp, int i)
  {
    char *p=(char*)&dp;
    for (int j=7;j>0;j--)
    {
      if (i>j*8-1)
      {
        p = (char*)&dp + j;
        i = i-(j*8);
        break;
      }
    }
    return (*p >> i)&1;
  }


  // filp ith bit of ch
  static inline unsigned char flipBit (unsigned char ch, int i)
  {
    int bit = getBit (ch, i);
    unsigned mask = 1 << i;
    if (bit == 0)	return mask | ch;
    else	return ~mask & ch;
  }

  // filp ith bit in * cp
  static inline void PflipBit (char * cp, int i)
  {
    int bit = getBit (*cp, i);
    unsigned mask = 1 << i;
    if (bit == 0)	*cp = mask | *cp;
    else	*cp = ~mask & *cp;
    return ;
  }

  // print all the bits in ch
  static inline void printBit (unsigned char ch)
  {
    for (int i=0;i<8;i++)	cout<<(int)getBit(ch,7-i);
  }

  static inline void printBit (char * ch)
  {
    for (int i=0;i<8;i++)	cout<<(int)getBit(*ch,7-i);
  }

  static inline void printBit(double *dp)
  {
    for (int i=0;i<64;i++)	cout <<(int)getBit(*dp,63-i);
  }

  static inline void printBit(int *ip)
  {
    for (int i=0;i<32;i++)	cout<< (int)getBit(*ip,31-i);
  }

  static inline void printBit(void *p, int range)
  {
    int nu = range/8;
    int re = range%8;
    if (re > 0)
    {
      for (int i=0;i<re;i++)	cout <<(int)getBit(*((char*)p+nu),re-1-i);
    }
    for (int i=0;i<nu;i++)
      printBit((char*)p+(nu-i-1));
  }

  // get higher bit in range 0~7
  static inline int getBit (char * ch, int range)
  {
    int x=0;
    for (int i=0;i<range;i++)	x=x*10+(int)getBit(*ch,7-i);
    return x;
  }

  static inline void randomFlip (char * cp)
  {
    srand (time(NULL));
    int i = rand()%8;
    PflipBit(cp,i);
  }

  static inline void randomFlip (int *ip)
  {
    int i = getRand()%(sizeof(int)*8);
    char *cp=(char*)ip;
    for (int j=3;j>0;j--)
    {
      if (i>j*8-1)
      {
        cp = (char *)ip+j;
        i=i-(j*8);
        break;
      }	
    }
    PflipBit (cp,i);
  }
  static inline void randomFlip (double *dp)
  {
    int i = getRand()%(sizeof(double)*8);
    char * cp=(char*)dp;
    for (int j=7;j>0;j--)                                                      
    {
      if (i>j*8-1)
      {
        cp = (char*)dp + j;
        i = i - (j*8);
        break;
      }
    }
    PflipBit (cp,i);

    cout << " Bit flip operaton is done" <<endl ;
  }

  //Emin you should write randomFlip method for this

  static inline void randomFlip(double *dp , int range1 , int range2)
  {
    //int i = getRand()%(sizeof(double)*8);
    cout << " Random Flip Operation Range 1 = " <<range1<<" and Range 2 =" << range2 <<endl ;

    srand(time(NULL));
    int i= ( getRand()%(range2 + 1 - range1) )+ range1 ;    
    char * cp=(char*)dp;

    cout << " Bit flip operaton is done and injected bit is = " <<i<<endl ;

      for (int j=7;j>0;j--)                                                      
      {
        if (i>j*8-1)
        {
          cp = (char*)dp + j;
          i = i - (j*8);
          break;
        }
      }

    PflipBit(cp, i) ;

    

  //Emin 

  }

  static inline void flipDoubleBit (double *dp, int i)
  {
    char * cp=(char*)dp;
    for (int j=7;j>0;j--)                                                      
    {
      if (i>j*8-1)
      {
        cp = (char*)dp + j;
        i = i - (j*8);
        break;
      }
    }
    PflipBit (cp,i);
  }


  static inline void randomFlip(map <int *,long int> imap)
  {
    srand (time(NULL));
    if (imap.size()==0)	
    {
      cerr <<"RandomFlip(): Map has no contect!"<<endl;
      exit(10);
    }
    if (imap.size()==1)
    {
      srand (time(NULL));
      cout <<"second: "<<imap.begin()->second<<endl;
      long offset = rand()%(imap.begin()->second);
      int * p = imap.begin()->first;
      p+=offset/sizeof(int);
      cout <<"offset "<<offset<<"\tflippin"<<*p;
      randomFlip(p);
      cout << "\tto " <<*p<<endl;	
    }
    else {
      int i = rand()%imap.size();
      int j=0;
      cout << "map size: "<<imap.size();
      for (map <int *,long int>::iterator it=imap.begin();it!=imap.end();it++,j++)
      {
        if (j==i)
        {
          srand (time(NULL));
          long offset = rand()%(it->second);
          int * p = it->first;
          p += offset/sizeof(int);
          cout <<"\toffset "<<offset<<"\tflipping "<<*p;
          randomFlip(p);
          cout <<"\tto "<<*p<<endl;;
        }
      }
    }
  }

  static inline void randomFlip(map <double *,long int> imap)
  {
    
    srand (time(NULL));
    if (imap.size()==0)	
    {
      cout <<"RandomFlip(): Map has no contect!"<<endl;
      return;
    }
    if (imap.size()==1)
    {
      srand (time(NULL));
      cout <<"second: "<<imap.begin()->second<<endl;
      long offset = rand()%(imap.begin()->second);
      double * p = imap.begin()->first;
      p+=offset/sizeof(double);
      cout <<"offset "<<offset<<"\tflipping "<<*p;
      randomFlip(p);
      cout << "\tto " <<*p<<endl;	
    }
    else {
      int i = rand()%imap.size();
      int j=0;
      cout << "map size: "<<imap.size();
      for (map <double *,long int>::iterator it=imap.begin();it!=imap.end();it++,j++)
      {
        if (j==i)
        {
          srand (time(NULL));
          long offset = rand()%(it->second);
          double * p = it->first;
          p += offset/sizeof(double);
          cout <<"\tMap: "<<j<<"\toffset "<<offset<<"\tflipping "<<*p;
          randomFlip(p);
          cout <<"\tto "<<*p<<endl;;
        }
      }
    }
  }
};


#endif

