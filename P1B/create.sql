CREATE TABLE Movie (
	id INT,
	title VARCHAR(100) NOT NULL,
	year INT,
	rating VARCHAR(10),
	company VARCHAR(50),
	PRIMARY KEY (id),
	CHECK (year > 0 AND year <= 2015)
) ENGINE=INNODB;

CREATE TABLE Actor (
	id INT,
	last VARCHAR(20) NOT NULL,
	first VARCHAR(20) NOT NULL,
	sex VARCHAR(6),
	dob DATE NOT NULL,
	dod DATE,
	PRIMARY KEY (id),
	CHECK (dob <= 2015)
) ENGINE=INNODB;

CREATE TABLE Director (
	id INT,
	last VARCHAR(20) NOT NULL,
	first VARCHAR(20) NOT NULL,
	dob DATE NOT NULL,
	dod DATE,
	PRIMARY KEY (id),
	CHECK (dob <= 2015)
) ENGINE=INNODB;

CREATE TABLE MovieGenre (
	mid INT,
	genre VARCHAR(20),
	FOREIGN KEY (mid) REFERENCES Movie(id)
) ENGINE=INNODB;

CREATE TABLE MovieDirector (
	mid INT,
	did INT,
	FOREIGN KEY (mid) REFERENCES Movie(id),
	FOREIGN KEY (did) REFERENCES Director(id)
) ENGINE=INNODB;

CREATE TABLE MovieActor (
	mid INT,
	aid INT,
	role VARCHAR(50),
	FOREIGN KEY (mid) REFERENCES Movie(id),
	FOREIGN KEY (aid) REFERENCES Actor(id)

) ENGINE=INNODB;

CREATE TABLE Review (
	name VARCHAR(20),
	time TIMESTAMP,
	mid INT,
	rating INT,
	comment VARCHAR(500),
	FOREIGN KEY (mid) REFERENCES Movie(id),
	CHECK (rating >= 0 AND rating <= 5)
) ENGINE=INNODB;

CREATE TABLE MaxPersonID (
	id INT
) ENGINE=INNODB;

CREATE TABLE MaxMovieID (
	id INT
) ENGINE=INNODB;



