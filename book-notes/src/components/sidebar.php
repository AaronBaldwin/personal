<div class='sidebar'>
  <?php

  # Look in specified data directory, which will contain a list of directories
  # Each directory represents a book that has been annotated and should be displayed
  $bookListings = new DirectoryIterator($booknotesDirectory);
  foreach($bookListings as $fileinfo) {
    if($fileinfo->isDot()) continue;

    # For now, the name of the directory should match the name of the book in question
    # Many books will have spaces in their name, should handle this later
    $bookName = $fileinfo->getFileName(); # "infinite-jest"
    $formattedBookName = formatBookAndChapterText($bookName); #"Infinite Jest"

    $bookDivClassName = $selectedBook === $bookName ? "book open" : "book";
    echo "<div class='$bookDivClassName'>";
    echo
      "<div class='click-wrapper'>
        <i class='fa fa-chevron-right'></i>
        <p id='$bookName'>$formattedBookName</p>
      </div>";

    # Look at the book-specific directory, i.e. ./books/tartuffe
    # Take all listings there and display them as page links
    # if a file called "manifest" is present,
    # we will use it as the listings instead of the directory contents
    $manifestFilePath = "$booknotesDirectory/$bookName/manifest";
    $bookSections = file_exists($manifestFilePath) ? file($manifestFilePath) :
      scandir("$booknotesDirectory/$bookName"); # "./books/infinite-jest"

    # Generate a link for each section as <li><a>
    echo "<ul>";
    foreach($bookSections as $sectionName) {
      $sectionName = trim($sectionName);
      if($sectionName === "." OR $sectionName === "..") continue;
      $sectionLink = "/$bookName/$sectionName";
      $formattedSectionName = formatBookAndChapterText($sectionName);
      $liClass = strcmp($selectedSection, $sectionName) == 0 ? "selected" : "a";
      echo "<li class='$liClass'><a href='$sectionLink'>$formattedSectionName</a></li>";
    }
    echo "</ul>"; # End list of sections for this book
    echo "</div>"; # End book entry in the sidebar
  }
  ?>
</div>