<?php include 'header.php' ?>
<body>
	<h2 class="form_header">Create Director</h2>
	<form id="create_director_form" action='create_person.php' method='GET'>
		<input name="create_person" type="hidden" value="true"/>
		<input name="person_type" type="hidden" value="director"/>

			<label class="form_label">First Name: </label><input class="form_input" type="text" name="first"/><br/><br/>
			<label class="form_label">Last Name: </label><input class="form_input" type="text" name="last"/><br/><br/>
			<label class="form_label">DOB: </label><input class="form_input" type="text" name="dob"/><br/><br/>
			<label class="form_label">DOD: </label><input class="form_input" type="text" name="dod"/><br/><br/>

		<input class="form_submit" type='submit' value='Create Director'/>
	</form>
</body>