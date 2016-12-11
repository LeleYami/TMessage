#include "read_write.cpp"

void hserv() {

   TServerSocket *ss = new TServerSocket(9090, kTRUE);

   // Accept a connection and return a full-duplex communication socket.
   TSocket *s = ss->Accept();

   // tell the clients to start
   s->Send("go");

   // Close the server socket
   ss->Close();

   // Get the remote addresses.
   TInetAddress adr = s->GetInetAddress();
   adr.Print();

   //this class monitors activity on a number of network sockets
   TMonitor *mon = new TMonitor;

   mon->Add(s);

   while (1) {
      TMessage *mess;
      TSocket  *s;

      s = mon->Select();

      s->Recv(mess);

      if (mess->What() == kMESS_STRING) {
         char str[64];
         mess->ReadString(str, 64);
         printf("Client s: %s\n", str);
         mon->Remove(s);
         if (mon->GetActive() == 0) {
            printf("No more active clients... stopping\n");
            break;
         }
      } else if (mess->What() == kMESS_OBJECT) {
         TObject* m= mess->ReadObject(mess->GetClass());
         m->Print();
         //send objects to the client
         TMessage mess2(kMESS_OBJECT);
         mess2.WriteObject(m);
         s->Send(mess2);
      } else {
         printf("*** Unexpected message ***\n");
      }

      delete mess;
   }

   printf("Client: bytes recv = %d, bytes sent = %d\n", s->GetBytesRecv(),
          s->GetBytesSent());

   // Close the socket.
   s->Close();
}
