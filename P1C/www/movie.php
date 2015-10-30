<?php
	include 'header.php';
	include 'db_functions.php';
	print "<body>";
	if ($_GET["movie_id"]){
		$db_connection = create_connection("localhost", "cs143", "");
		$movie_id = intval(sanitize_string($_GET["movie_id"], $db_connection));
		$movie_base_query = "select * from Movie where id=%d";
		$movie_query = sprintf($movie_base_query, $movie_id);
		//print $movie_query . "<br/>";
		$movie = run_query($movie_query, $db_connection);

		$movie_attr = mysql_fetch_array($movie, MYSQL_ASSOC);

		$movie_genre_base_query = "select genre from MovieGenre where mid=%d";
		$movie_genre_query = sprintf($movie_genre_base_query, $movie_id);
		$movie_genres = run_query($movie_genre_query, $db_connection);
		$movie_genre_string = "";
		while ($movie_genre_row = mysql_fetch_array($movie_genres, MYSQL_ASSOC)){
			$movie_genre_string .= ($movie_genre_row["genre"] . " ");
		}

		printf("<h2 class='page_header'>%s (%s)</h2>", $movie_attr["title"], $movie_attr["year"]);
		printf("<h4 class='page_centered'>%s | %s | %s</h4>", $movie_attr["rating"], $movie_attr["company"], $movie_genre_string);

		$avg_rating_base_query = "select avg(rating) from Review where mid=%d";
		$avg_rating_query = sprintf($avg_rating_base_query, $movie_id);
		$avg_rating_result = run_query($avg_rating_query, $db_connection);
		$avg_rating = mysql_fetch_array($avg_rating_result, MYSQL_ASSOC)["avg(rating)"];
		if ($avg_rating) printf("<h4 class='page_centered'>Average %d/5 stars </h4>", $avg_rating);
		

		$movie_actor_base_query = "select aid,role from MovieActor where mid=%d";
		$movie_actor_query = sprintf($movie_actor_base_query, $movie_id);
		//print $movie_actor_query . "<br/>";
		$movie_actors = run_query($movie_actor_query, $db_connection);
		
		$url_safe_title = str_replace(" ", "+", $movie_attr["title"]);
		$movie_actor_link = sprintf("movie_actor_form.php?movie_id=%d&movie_title=%s", $movie_id ,$url_safe_title);
		print "<h2>Actors <a href=$movie_actor_link>(add)</a></h2>";
		if (mysql_num_rows($movie_actors) > 0){
			$aids = array();
			$roles = array();
			while ($movie_actor_row = mysql_fetch_array($movie_actors, MYSQL_ASSOC)){
				array_push($aids,$movie_actor_row["aid"]);
				$roles[$movie_actor_row["aid"]] = $movie_actor_row["role"];
			}
			$aid_string = implode(",",$aids);
			$actor_base_query = "select * from Actor where id in (%s)";
			$actor_query = sprintf($actor_base_query, $aid_string);
			//print $actor_query . "<br/>";
			$actors = run_query($actor_query, $db_connection);

			print "<ul>";
			while ($actor_row = mysql_fetch_array($actors, MYSQL_ASSOC)){
				$actor_link = sprintf("actor.php?actor_id=%d", intval($actor_row["id"]));
				printf("<li><a href=%s>%s %s</a> ... %s</li>", $actor_link, $actor_row["first"], $actor_row["last"], $roles[$actor_row["id"]]);
			}
			print "</ul>";
		}
		print "<hr/>";
		
		$movie_director_base_query = "select did from MovieDirector where mid=%d";
		$movie_director_query = sprintf($movie_director_base_query, $movie_id);
		//print $movie_director_query . "<br/>";
		$movie_directors = run_query($movie_director_query, $db_connection);

		$url_safe_title = str_replace(" ", "+", $movie_attr["title"]);
		$movie_director_link = sprintf("movie_director_form.php?movie_id=%d&movie_title=%s", $movie_id ,$url_safe_title);
		print "<h2>Directors <a href=$movie_director_link>(add)</a></h2>";
		if (mysql_num_rows($movie_directors) > 0){
			$dids = array();
			while ($movie_director_row = mysql_fetch_array($movie_directors, MYSQL_ASSOC)){
				array_push($dids, $movie_director_row['did']);
			}
			$did_string = implode(",",$dids);
			$director_base_query = "select * from Director where id in (%s)";
			$director_query = sprintf($director_base_query, $did_string);
			//print $director_query . "<br/>";
			$directors = run_query($director_query, $db_connection);

			print "<ul>";
			while ($director_row = mysql_fetch_array($directors, MYSQL_ASSOC)){
				$director_link = sprintf("director.php?director_id=%d", intval($director_row['id']));
				printf("<li><a href=%s>%s %s</a></li>", $director_link, $director_row["first"], $director_row["last"]);
			}
			print "</ul>";	
		}
		print "<hr/>";

		$review_base_query = "select * from Review where mid=%d";
		$review_query = sprintf($review_base_query, $movie_id);
		//print $review_query . "<br/>";
		$reviews = run_query($review_query, $db_connection);

		$url_safe_title = str_replace(" ", "+", $movie_attr["title"]);
		$review_link = sprintf("review_form.php?movie_id=%d&movie_title=%s", $movie_id, $url_safe_title);
		print "<h2>Reviews <a href=$review_link>(add)</a></h2>";
		if (mysql_num_rows($reviews) > 0){
			while ($review_row = mysql_fetch_array($reviews, MYSQL_ASSOC)){
				$review_day = explode(" ", $review_row["time"])[0];
				printf("<p><b>%s</b> %d/5 stars (%s)</p>", $review_row["name"], $review_row["rating"], $review_day);
				print "<ul>";
				printf("<li>%s</li>", $review_row["comment"]);
				print "</ul>";
				print "<br/>";
			}
		}
		else {
			print "<p>Be the first to write a review!</p>";
		}
		print "<hr/>";
		close_connection($db_connection);
	}
	print "</body>";
?>