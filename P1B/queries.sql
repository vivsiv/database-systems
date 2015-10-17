-- Names of all actors in "Die Another Day"
SELECT first, last
FROM Actor
WHERE Actor.id IN (
	SELECT aid
	FROM Movie, MovieActor
	WHERE Movie.id = MovieActor.mid AND Movie.title = "Die Another Day"
);

-- Count of all actors who acted in multiple movies
SELECT COUNT(*)
FROM (
	SELECT *
	FROM MovieActor
	GROUP BY aid
	HAVING COUNT(mid) >= 2
) AS M;

-- Find All Meg Ryan RomComs
SELECT DISTINCT title
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

