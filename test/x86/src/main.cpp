#include "../../../include/npp9.0.1/addin.h"

namespace npp = npp090001;

int main(int argc, char** argv) {
  auto status = NotesInitExtended(argc, argv);
  if (ERR(status) == NOERROR) {
    npp::addin::logMessageText("Hello npp9.0.1!");
    NotesTerm();
    return 0;
  }
  else {
    return status;
  }
}