/**********************************************************************
 Created on : 22/10/2022
 Purpose    : Check the validity of the luminosity blocks in data files
 Author     : Indranil Das, Visiting Fellow
 Email      : indranil.das@cern.ch | indra.ehep@gmail.com
**********************************************************************/
// rapidjson/example/simpledom/simpledom.cpp`
#include "../rapidjson/document.h"
// #include "../rapidjson/writer.h"
// #include "../rapidjson/stringbuffer.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace rapidjson;

int main() {
  
  std::ifstream inputFile( "weightUL/LumiGoldenJson/2016/Cert_271036-284044_13TeV_ReReco_07Aug2017_Collisions16_JSON.txt" );
  //std::ifstream inputFile( "weightUL/LumiGoldenJson/2017/Cert_294927-306462_13TeV_EOY2017ReReco_Collisions17_JSON_v1.txt" );
  //std::ifstream inputFile( "weightUL/LumiGoldenJson/2018/Cert_314472-325175_13TeV_17SeptEarlyReReco2018ABC_PromptEraD_Collisions18_JSON.txt" );
  std::stringstream jsonDocumentBuffer;
  std::string inputLine;

  int line = 1;
  while ( std::getline( inputFile, inputLine ) ){
    jsonDocumentBuffer << inputLine << "\n";
    std::cout << "Line : " << line << std::endl;
    std::cout << inputLine << std::endl;
    std::cout << "Line : " << line << std::endl;
    line++;
  }
  rapidjson::Document config;
  config.Parse( jsonDocumentBuffer.str( ).c_str( ) );

  assert(config.IsObject());

  //274388
  unsigned int run  = 273492;//2016
  //unsigned int run  = 306458; // 2017
  //unsigned int run  = 324970;
  std::string run_no = std::to_string(run);
  
  if( config.HasMember(run_no.data()) ){
    
  const Value& a = config[run_no.data()];
  assert(a.IsArray());

    for (SizeType i = 0; i < a.Size(); i++){ // Uses SizeType instead of size_t
      printf("a[%d] : %d\n", i,a[i].Size());
      assert(a[i].IsArray());
      const Value& b = a[i];
      for (SizeType j = 0; j < b.Size(); j++)
	printf("\tb[%d] = %d\n", j, b[j].GetInt());
    }
  }else{
    std::cerr << "Run number : " << run_no << " not found " << std::endl;
  }
  
  return 0;
}
