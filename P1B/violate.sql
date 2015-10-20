INSERT INTO Movie VALUES (2,"Top Gun",1990,"PG-13","Paramount");
-- Inserting a duplicate id into Movie Violates the Primary Key on id for Movie
-- ERROR 1062 (23000): Duplicate entry '2' for key 'PRIMARY'

DELETE FROM Movie where id=2;
-- Deleting/Updating a Movie's id Violates a MovieGenre's foreign key on mid if the movie is in the MovieGenre table
-- ERROR 1451 (23000): Cannot delete or update a parent row: a foreign key constraint fails (`TEST`.`MovieGenre`, CONSTRAINT `MovieGenre_ibfk_1` FOREIGN KEY (`mid`) REFERENCES `Movie` (`id`))

-- Deleting/Updating a Movie's id Violates a MovieActor's foreign key on mid if the movie is in the MovieActor table
-- ERROR 1451 (23000): Cannot delete or update a parent row: a foreign key constraint fails (`TEST`.`MovieActor`, CONSTRAINT `MovieActor_ibfk_1` FOREIGN KEY (`mid`) REFERENCES `Movie` (`id`))

-- Deleting a Movie Violates a MovieDirector's foreign key on mid if the movie is in the MovieDirector table
-- ERROR 1451 (23000): Cannot delete or update a parent row: a foreign key constraint fails (`TEST`.`MovieDirector`, CONSTRAINT `MovieDirector_ibfk_1` FOREIGN KEY (`mid`) REFERENCES `Movie` (`id`))

-- Deleting a Movie Violates a Review's foreign key on mid if the movie is in the Review table
-- ERROR 1451 (23000): Cannot delete or update a parent row: a foreign key constraint fails (`TEST`.`Review`, CONSTRAINT `Review_ibfk_1` FOREIGN KEY (`mid`) REFERENCES `Movie` (`id`))
-- NOTE: Since there are no entries in the Review table at the moment this error never occured.


INSERT INTO Actor VALUES (11,"Cruise","Tom","male",1975-05-25,NULL);
-- Inserting a duplicate id into Actor Violates the Primary Key on id for Actor
-- ERROR 1062 (23000): Duplicate entry '11' for key 'PRIMARY'

DELETE FROM Actor WHERE id=180;
-- Deleting/Updating an Actor's id violates a MovieActor's foreign key on aid if the actor is in the MovieActor Table
-- ERROR 1451 (23000): Cannot delete or update a parent row: a foreign key constraint fails (`TEST`.`MovieActor`, CONSTRAINT `MovieActor_ibfk_2` FOREIGN KEY (`aid`) REFERENCES `Actor` (`id`))

INSERT INTO Director VALUES (16,"Whedon","Joss",1975-05-25,NULL);
-- Inserting a duplicate id into Director Violates the Primary Key on id for Director
-- ERROR 1062 (23000): Duplicate entry '16' for key 'PRIMARY'

DELETE FROM Director WHERE id=112;
-- Deleting/Updating a Director's id violates a MovieDirector's foreign key on did if the director is in the MovieDirector Table
-- ERROR 1451 (23000): Cannot delete or update a parent row: a foreign key constraint fails (`TEST`.`MovieDirector`, CONSTRAINT `MovieDirector_ibfk_2` FOREIGN KEY (`did`) REFERENCES `Director` (`id`))

INSERT INTO Movie VALUES (5000,"Movie From The Future", 3000, "PG-13", "Alien Movies");
-- Inserting a Movie made after 2015 violates the check constraint on year.

INSERT INTO Review VALUES ("Way too Excited", 2015-10-19,1,5000,"WOOOOOO");
-- Inserting a review with a rating higher than 5 violates the review check constraint

INSERT INTO Actor VALUES (5000,"Exist","Doesn't",2075-10-30);
-- Inserting an actor born after 2015 violates the Actor check constraint