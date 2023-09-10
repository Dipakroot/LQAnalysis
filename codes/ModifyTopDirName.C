int ModifyTopDirName(const char *infile, const char *inhistname, const char *outfile, const char *outhistname)
{
  bool isVerbose = 0;
  TFile *fin1 = TFile::Open(infile);
  TDirectory *dir1 = (TDirectory *)fin1->Get(inhistname);

  if(isVerbose)
    cout << dir1->GetName() << endl;
  
  TFile *fout = TFile::Open(outfile,"recreate");
  TDirectory *base = fout->mkdir(outhistname);
  TIter nextkey( dir1->GetListOfKeys() );
  TKey *key, *oldkey=0;
  while ( (key = (TKey*)nextkey())) {
    TDirectoryFile *obj = (TDirectoryFile *)key->ReadObj();
    if(isVerbose)
      cout<< key->GetClassName() << ", "<< obj->GetName() << endl;
    TDirectory *outdir = base->mkdir(obj->GetName());
    TIter nextkey1( obj->GetListOfKeys() );
    TKey *key1;
    while ( (key1 = (TKey*)nextkey1())) {
      TDirectoryFile *obj1 = (TDirectoryFile *)key1->ReadObj();
      if(isVerbose)
	cout<<"\t" <<  key1->GetClassName() << ", "<< obj1->GetName() << endl;
      TDirectory *outdir1 = outdir->mkdir(obj1->GetName());
      TIter nextkey2( obj1->GetListOfKeys() );
      TKey *key2;
      while ( (key2 = (TKey*)nextkey2())) {
	TObject *obj2 = key2->ReadObj();
	outdir1->cd();
	//if(isVerbose)
	//cout<<"\t\t" <<  key2->GetClassName() << ", "<< obj2->GetName() << endl;
	obj2->Write();
      }//key2 key      
    }//key1 loop
  }
  fout->Close();
  delete fout;
  fin1->Close();
  delete fin1;
  
  return true;
}
