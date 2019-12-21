Js.log("Hello, BuckleScript and Reason!");


Node.Fs.readFileAsUtf8Sync("../generations.txt")
|> Js.String.trim
|> Js.String.split("\n")
|> Array.map(Js.String.trim)
|> Array.map(Js.String.split(";"))
|> Js.log
