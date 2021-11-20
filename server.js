const express = require("express");
const mail = require('./utils/mailer')

const app = express();
const PORT = process.env.port || 3000;

app.use(express.json());

app.get('/', (req, res) => {
    res.send(`<h1> UNDER CONSTRUCTION </h1>`)
});

app.post('/', (req, res) => {
    mail(req.body, res);
});

app.listen(PORT, console.log(`Listening on PORT ${PORT}`));