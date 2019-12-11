Node.Fs.readFileAsUtf8Sync("./terreng.txt")
|> Js.String.replace("\n", "")
|> Js.String.trim
|> Js.log
