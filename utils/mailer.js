const nodemailer = require("nodemailer");

function sendWarning(details, res) {
    const transporter = nodemailer.createTransport({
        service: "hotmail",
        auth: {
            user: process.env.email,
            pass: process.env.pass
        }
    });
    const mail = {
        from: process.env.email,
        to: details.email,
        subject: `Warning mail from drunk driver system`,
        text: `Alcohol was detected by the device with the ID: ${details.id}. 
        Please take appropriate action.`
    }

    transporter.sendMail(mail, (err, info) => {
        res.send(err ? err : info);
    });
}

module.exports = sendWarning;