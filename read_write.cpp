#include "../include/TFile.h"
#include "Sclass.h"

void write_it(){
    std::cout<<"write it..."<<std::endl;
    TFile *f=TFile::Open("test.root","recreate");

    Sclass* obj=new Sclass();
    obj->SetX(42.1);
    obj->SetY(1.24);
    obj->Write("anObject");

    f->Close();
    std::cout<<"write it done."<<std::endl;
}

void read_it(){
   std::cout<<"read it..."<<std::endl;
   TFile* f=TFile::Open("test.root");
   if(!f){
      std::cerr<<"Can't open file test.root."<<std::endl;
      return;
   }

   Sclass* obj=dynamic_cast<Sclass*>(f->Get("anObject"));
   if(!obj){
      std::cerr<<"Can't find the object anObject."<<std::endl;
      return;
   }
   obj->Print();
   std::cout<<"read it done."<<std::endl;
}

void read_write(){
    write_it();
    read_it();
}

int main(){
    read_write();
}
