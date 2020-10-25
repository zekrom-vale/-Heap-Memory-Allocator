

void* Mem_Init(int sizeOfRegion){
  void* v=mmap(NULL, (size_t)sizeOfRegion, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, 0, sysconf(_SC_PAGE_SIZE));
  return v==MAP_FAILED?NULL:v;
}
