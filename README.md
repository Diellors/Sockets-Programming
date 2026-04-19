# Sockets-Programming

Ky projekt realizon një komunikim të thjeshtë në kohë reale midis një Serveri dhe një Klienti duke përdorur protokollin TCP dhe librarinë Winsock2 në C++.

Si funksionon
Serveri: Përdor listen() dhe accept() për të pritur lidhje. Kur një klient lidhet, serveri krijon një thread të ri (CreateThread) për të menaxhuar komunikimin, duke lejuar shërbimin e shumë klientëve njëkohësisht.

Klienti: Lidhet me serverin përmes IP-së 127.0.0.1 dhe portit 8080. Pasi lidhet, klienti dërgon rolin e tij dhe hap një thread të dedikuar për të marrë mesazhe, ndërsa thread-i kryesor mbetet i lirë për të dërguar mesazhe të reja.

Përdorimi
Serveri: Kompilo dhe ekzekuto server.cpp. Ai do të qëndrojë në pritje të lidhjeve.

Klienti: Kompilo dhe ekzekuto client.cpp.

Komunikimi: Pasi klienti të zgjedhë rolin e tij, të dy palët mund të shkëmbejnë mesazhe në terminal. Shkruani exit në klient për të mbyllur lidhjen.
