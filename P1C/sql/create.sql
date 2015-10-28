CREATE TABLE Movie (
	id INT,
	title VARCHAR(100) NOT NULL,
	year INT,
	rating VARCHAR(10),
	company VARCHAR(50),
	PRIMARY KEY (id),
	CHECK (year > 0 AND year <= 2015)
) ENGINE=INNODB;
-- Making id the primary key for movies (it must be unique for all movies)
-- Checking that all movie years are valid

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
-- Making id the primary key for actors (it must be unique for all actors)
-- Checking that all actor dates of birth are valid

CREATE TABLE Director (
	id INT,
	last VARCHAR(20) NOT NULL,
	first VARCHAR(20) NOT NULL,
	dob DATE NOT NULL,
	dod DATE,
	PRIMARY KEY (id),
	CHECK (dob <= 2015)
) ENGINE=INNODB;
-- Making id the primary key for directors (it must be unique for all directors)
-- Checking that all director dates of births are valid

CREATE TABLE MovieGenre (
	mid INT,
	genre VARCHAR(20),
	FOREIGN KEY (mid) REFERENCES Movie(id)
) ENGINE=INNODB;
-- Each movie in the MovieGenre table refers to a movie in the Movie table

CREATE TABLE MovieDirector (
	mid INT,
	did INT,
	FOREIGN KEY (mid) REFERENCES Movie(id),
	FOREIGN KEY (did) REFERENCES Director(id)
) ENGINE=INNODB;
-- Each movie in the MovieDirector table refers to a movie in the Movie table
-- Each director in the MovieDirector table refers to a director in the Director table

CREATE TABLE MovieActor (
	mid INT,
	aid INT,
	role VARCHAR(50),
	FOREIGN KEY (mid) REFERENCES Movie(id),
	FOREIGN KEY (aid) REFERENCES Actor(id)

) ENGINE=INNODB;
-- Each movie in the MovieActor table refers to a movie in the Movie table
-- Each director in the MovieActor table refers to an actor in the Actor table

CREATE TABLE Review (
	name VARCHAR(20),
	time TIMESTAMP,
	mid INT,
	rating INT,
	comment VARCHAR(500),
	FOREIGN KEY (mid) REFERENCES Movie(id),
	CHECK (rating >= 0 AND rating <= 5)
) ENGINE=INNODB;
-- Each movie in the Review table refers to a movie in the Movie table

CREATE TABLE MaxPersonID (
	id INT
) ENGINE=INNODB;

CREATE TABLE MaxMovieID (
	id INT
) ENGINE=INNODB;



