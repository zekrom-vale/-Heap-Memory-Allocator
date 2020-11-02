#include "error.h"


//#define E_NO_SPACE (1)
void error_noSpace(){
    m_error=E_NO_SPACE;
    exit(E_NO_SPACE);
}

//#define E_CORRUPT_FREESPACE (2)
void error_freeSpace(struct node* cur){
    
}
    //#define E_PADDING_OVERWRITTEN (3)
void error_head(struct header* head){
    if (head->magic != MAGIC){
        m_error=E_PADDING_OVERWRITTEN;
        exit(E_PADDING_OVERWRITTEN);
    }
}
//#define E_BAD_ARGS (4)

void error_args(int size) {
  if (size <= 0 || size > MAX_SIZE) {
    m_error = E_BAD_ARGS;
    exit(E_BAD_ARGS);
  }
}

void error_args_t(size_t size) {
  if (size > MAX_SIZE) {
    m_error = E_BAD_ARGS;
    exit(E_BAD_ARGS);
  }
}
//#define E_BAD_POINTER (5)