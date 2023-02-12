open Candy;
open List;

let conn = Redis_sync.Client.connect({host: "localhost", port: 6379});
let read = Worker.use(conn, "example_channel");

while (true) {
  read() ->> map(print_endline) ->> ignore;
};
