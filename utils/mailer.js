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
        html: `Alcohol was detected by the device with the ID: ${details.id}. Please take appropriate action.`
    }

    transporter.sendMail(mail, (err, info) => {
        if (err) res.status(500).send("Error");
        else res.send(info);
    });
}

module.exports = sendWarning;