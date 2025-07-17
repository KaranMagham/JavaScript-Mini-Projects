const express = require('express')
const app = express()
const port = 3000
const fs = require("fs")
const path = require("path")

const targetedpath = './Files';
const files = fs.readdirSync(targetedpath);

files.forEach((file) => {
  const absolutepath = path.join(targetedpath, file);

  if (fs.lstatSync(absolutepath).isDirectory()) return;

  const extension = path.extname(file).slice(1);

  const finalpath = path.join(targetedpath, extension)

  if (!fs.existsSync(finalpath)) {
    fs.mkdirSync(finalpath);
  }
  
      const lastjoining = path.join(finalpath, file)
  
      fs.renameSync(absolutepath, lastjoining)
  
      console.log(`${file} moved to ${extension}`)
})

app.get('/', (req, res) => {
  res.send('Hello World!')
})

app.listen(port, () => {
  console.log(`Example app listening on port ${port}`)
})
