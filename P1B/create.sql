CREATE TABLE Movie (
	id INT,
	title VARCHAR(100) NOT NULL,
	year INT,
	rating VARCHAR(10),
	company VARCHAR(50),
	PRIMARY KEY (id)
);

CREATE TABLE Actor (
	id INT,
	last VARCHAR(20) NOT NULL,
	first VARCHAR(20) NOT NULL,
	sex VARCHAR(6),
	dob DATE NOT NULL,
	dod DATE,
	PRIMARY KEY (id)
);

CREATE TABLE Director (
	id INT,
	last VARCHAR(20) NOT NULL,
	first VARCHAR(20) NOT NULL,
	dob DATE NOT NULL,
	dod DATE,
	PRIMARY KEY (id)
);

CREATE TABLE MovieGenre (
	mid INT,
	genre VARCHAR(20),
	FOREIGN KEY (mid) REFERENCES Movie(id)
);

CREATE TABLE MovieDirector (
	mid INT,
	did INT,
	FOREIGN KEY (mid) REFERENCES Movie(id),
	FOREIGN KEY (did) REFERENCES Director(id)
);

CREATE TABLE MovieActor (
	mid INT,
	aid INT,
	role VARCHAR(50),
	FOREIGN KEY (mid) REFERENCES Movie(id),
	FOREIGN KEY (aid) REFERENCES Actor(id)

);

CREATE TABLE Review (
	name VARCHAR(20),
	time TIMESTAMP,
	mid INT,
	rating INT,
	comment VARCHAR(500),
	FOREIGN KEY (mid) REFERENCES Movie(id)
);

CREATE TABLE MaxPersonID (
	id INT
);

CREATE TABLE MaxMovieID (
	id INT
);



