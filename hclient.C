#include "read_write.cpp"

void hclient()
{
   // Open connection to server
   TSocket *sock = new TSocket("localhost", 9090);

   // Wait till we get the start message
   char str[32];
   sock->Recv(str, 32);

   //open the file and get the object
   TFile f("test.root");
   Sclass* obj=dynamic_cast<Sclass*>(f.Get("anObject"));
   
   //create TMessage to save the object 
   TMessage mess(kMESS_OBJECT);
   mess.WriteObject(obj);
   
   // send message
   sock->Send(mess);  
        
   //receive object from the server
   //TMonitor *mon2 = new TMonitor;
   //mon2->Add(s2);

   while(1){
       TMessage *mess2;
       TSocket  *sock;

       //s = mon2->Select();
       sock->Recv(mess2);

       if (mess2->What() == kMESS_OBJECT){
          TObject* m2= mess2->ReadObject(mess2->GetClass());
          m2->Print();
      }
      break;
   }

   // tell server we are finished     
   sock->Send("Finished");         

   // Close the socket
   sock->Close();
}
