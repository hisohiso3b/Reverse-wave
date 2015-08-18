#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REV_WAVE_NAME "rev.wav"
#define MAX_SIZE 100000000

unsigned char header[44];
unsigned char wave[MAX_SIZE];
FILE *fpr;
long datasize;

int outputRevWave(unsigned char *revWav){
  FILE *fpw;
  if ((fpw = fopen(REV_WAVE_NAME, "wb")) == NULL) {
    printf("reverse output error\n");
  }
  fwrite(header, 1, 44, fpw);
  fwrite(revWav, 45, datasize, fpw);

  return 0;
}

int outWaveHeader(char *inputFileName){
  //char temp[44];
  int i;

  fpr = fopen(inputFileName, "rb");//ファイルオープン
  if (fpr == NULL) {
    printf("error");
    exit(EXIT_FAILURE);
  }

  fread(&header, sizeof(unsigned char), 44, fpr);

  for(i=0; i<4; i++){//識別子
    printf("%c",header[i]);
  }
  printf("\n");
  for(i=4; i<5; i++){//ファイルサイズ(byte単位)
    //printf("%02x ",wave[i]);
    printf("%ld ", header[i] + 256L * (header[i+1] + 256L * (header[i+2] + 256L * header[i+3])) );
  }
  printf("\n");
  for(i=8; i<12; i++){//RIFFの種類を表す識別子 'WAVE'
    printf("%c",header[i]);
  }
  printf("\n");
  for(i=12; i<16; i++){//タグ 1
    printf("%c",header[i]);
  }
  printf("\n");
  for(i=16; i<20; i++){//fmt チャンクのバイト数
    //printf("%02x ",wave[i]);
    printf("%ld ", header[i] + 256L * (header[i+1] + 256L * (header[i+2] + 256L * header[i+3])) );
  }
  printf("\n");
  for(i=20; i<22; i++){//フォーマットID
    printf("%02x ",header[i]);
  }
  printf("\n");
  for(i=22; i<24; i++){//チャンネル数
    printf("%02x ",header[i]);
  }
  printf("\n");
  for(i=24; i<28; i++){//サンプリングレート
    printf("%02x ",header[i]);
  }
  printf("\n");
  for(i=28; i<32; i++){//データ速度 (Byte/sec)
    printf("%02x ",header[i]);
  }
  printf("\n");
  for(i=32; i<34; i++){//ブロックサイズ (Byte/sample×チャンネル数)
    printf("%02x ",header[i]);
  }
  printf("\n");
  for(i=34; i<36; i++){//サンプルあたりのビット数 (bit/sample)
    printf("%02x ",header[i]);
  }
  printf("\n");
  for(i=36; i<40; i++){//data チャンク
    printf("%c",header[i]);
  }
  printf("\n");
  for(i=40; i<41; i++){//波形データのバイト数
    //printf("%02x ",wave[i]);
    datasize = header[i] + 256L * (header[i+1] + 256L * (header[i+2] + 256L * header[i+3]));
    printf("%ld ", datasize );
  }
  printf("\n");

  fread(&wave, sizeof(unsigned char), datasize, fpr);

  fclose(fpr);
  return 0;
}

int reverseWave(void){
  printf("reversing\n");

  int i;
  unsigned char temp[datasize];

  for(i=0; i<datasize; i++){
    temp[datasize-i] = wave[i];
  }

  outputRevWave(temp);
  return 0;
}


int main(){
  char *filename;
  int process;

  printf("input wave file name ->> ");
  scanf("%s",filename);
  outWaveHeader(filename);

  printf("reversing...\n");
  reverseWave();
  printf("REVERSE COMPLETE! The file name is ");
  printf(REV_WAVE_NAME);
  printf("\n");
  
  return 0;
}
