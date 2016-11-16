+#include "Assembler.h"
+#include <string>
+
+using namepsace std;
+
+void Assembler::read(string fileName){
+  string currentLine;
+  ifstream fileStream;
+  fileStream.open(fileName);
+  
+  while(getline(fileStream,currentLine){
+    //loop through the file, storing lines to be implemented
+  }
+}
+
+void Assember::write(string fileName){
+  ofstream fileStream;
+  fileStream.open(fileName);
+  
+  for(//number of iterations){
+    fileStream << "Output data" << endl;
+  }
+}
