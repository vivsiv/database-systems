<?php
	include 'header.php';
	print "<body>";
?>
<h2 class="form_header">Add a Review for: <?php print $_GET['movie_title'] ?></h2>
<form id="create_review" action="create_review.php" method="GET">
	<input name="create_review" type="hidden" value="true"/>
	<input type="text" name="movie_id" hidden="true" value="<?php print $_GET['movie_id'] ?>"/>
	<div>
		<label class="form_label">Review Name: </label><input class="form_input" type="text" name="review_name"/><br/>
		<label class="form_label">Rating (1-5): </label><input class="form_input"type="text" name="rating"/><br/>
		<label class="form_label">Comment: </label><textarea class="form_text_area" type="text" name="comment"></textarea>
	</div>
	<br/><br/><br/><br/><br/><br/><br/><br/>
	<input class="form_submit" type='submit' value='Create Review'/>
</form>
<?php print "<body>"; ?>