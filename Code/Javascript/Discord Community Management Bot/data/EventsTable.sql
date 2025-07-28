CREATE TABLE History (
    WeekStart DATE,
    WeekEnd DATE,
    WeekNum INTEGER(6),
    Recuits INTEGER(3),
    Rally INTEGER(3)
);

CREATE TABLE Events (
    WeekNum INTEGER(6),
    HostID INTEGER(18),
    Attendance INTEGER(4),
    Game VARCHAR(6)
);