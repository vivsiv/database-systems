-- To find all the actors in Die another day I joined the Movie and MovieActor tables to get the set of aid's in Die Another Day.
-- Then I went through each actor in the Actor table to see if they were in this set, I selected the actors that were and printed
-- their first and last names concatenated together
SELECT CONCAT(first, " ", last) AS "Actors in Die Another Day"
FROM Actor
WHERE Actor.id IN (
	SELECT aid
	FROM Movie, MovieActor
	WHERE Movie.id = MovieActor.mid AND Movie.title = "Die Another Day"
);

-- To get the number of actors in multiple movies I first grouped entries in the MovieActor table by aid, I then selected those groups
-- that had 2 or mid's associated with them. Finally I counted the number of groups I had.
SELECT COUNT(*) AS "Number of Actors in multiple movies"
FROM (
	SELECT *
	FROM MovieActor
	GROUP BY aid
	HAVING COUNT(mid) >= 2
) AS M;

-- To find all Meg Ryan RomComs I joined the Actor and MovieActor tables to get the set of mid's with Meg Ryan in them.
-- I then joined the Movie and Movie Genre tables and selected those tuples that were in the set of mid's with meg ryan
-- and the set of movies with genre Romance or Comedy
SELECT DISTINCT title AS "Meg Ryan RomComs"
FROM Movie, MovieGenre
WHERE Movie.id = MovieGenre.mid AND
Movie.id IN (
	SELECT mid
	FROM Actor, MovieActor
	WHERE Actor.id = MovieActor.aid AND
	Actor.first="Meg" AND 
	Actor.last="Ryan"
) AND 
(MovieGenre.genre="Romance" OR MovieGenre.genre="Comedy");

