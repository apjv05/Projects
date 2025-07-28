const Days = 14;
const Hours = 24;
const Mins = 60;
const Seconds = 60;
const Milliseconds = 1000;
const TwoWeeks = Days * Hours * Mins * Seconds * Milliseconds;
//two weeks ago in milliseconds

const Vars = {
    Today: new Date().toISOString().slice(0, 10),
    Threshold: new Date(Date.now() - TwoWeeks).toISOString().slice(0, 10),
};

module.exports = Vars;