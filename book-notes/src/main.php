<?php
  require('./components/quote.php');
  # URL is in the format /bookName/sectionName
  # These methods are responsible for parsing that
  function getBookFromUrl(): string {
    $urlParts = explode("/", $_SERVER['REQUEST_URI']);
    return $urlParts[1] !== NULL ? $urlParts[1] : "";
  }

  function getSectionFromUrl(): string {
    $urlParts = explode("/", $_SERVER['REQUEST_URI']);
    return $urlParts[2] !== NULL ? $urlParts[2] : "";
  }

  function formatBookAndChapterText($text): string {
	  $text = str_replace("-", " ", $text);
    $text = ucwords($text);
    return $text;
  }

  $booknotesDirectory = './books';
  $selectedBook = getBookFromUrl();
  $formattedSelectedBookTitle = formatBookAndChapterText($selectedBook);
  # Sections are page divisions for the site, based on divisions of the book (chapters/acts).
  $selectedSection = getSectionFromUrl();
  $formattedSelectedSection = formatBookAndChapterText($selectedSection);

  # The "manifest" file is treated special if present- it specifes the order of sections for this book listing
  $selectedBookManifestFilePath = "$booknotesDirectory/$selectedBook/manifest";
  $selectedBookSections =
    file_exists($selectedBookManifestFilePath) ?
    file($selectedBookManifestFilePath, FILE_IGNORE_NEW_LINES) :
    scandir("$booknotesDirectory/$selectedBook"); # "./books/infinite-jest";
  
  # Determine the previous and next sections relative to currently selected one
  # These are linked at the top of each section
  $selectedSectionIndex = array_search($selectedSection, $selectedBookSections);
  $previousSectionUrl = $selectedSectionIndex <= 0 ? null :
    $selectedBookSections[$selectedSectionIndex - 1];
  $nextSectionUrl = $selectedSectionIndex === sizeof($selectedBookSections) ? null :
    $selectedBookSections[$selectedSectionIndex + 1];
?>

<!DOCTYPE html>
<html>
  <head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1, maximum-scale=1">
    <title>Dramatic Analysis</title>
    <link rel="shortcut icon" type="image/png" href="/favicon.svg"/>
    <link rel="stylesheet" href="/stylesheet.css" type="text/css">
    <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css">
    <link href="https://fonts.googleapis.com/css?family=Shadows+Into+Light" rel="stylesheet">
    <link href="https://stackpath.bootstrapcdn.com/font-awesome/4.7.0/css/font-awesome.min.css" rel="stylesheet">
    <script src="https://ajax.googleapis.com/ajax/libs/jquery/2.2.0/jquery.min.js"></script>
    <script src="/main.js"></script>
  </head>

  <body>
    <div class='book-notes'>
      <?php require('./components/header.php'); ?>
      <div class='main'>
        <?php require('./components/sidebar.php'); ?>
        <?php
          if($selectedBook !== NULL AND $selectedSection !== NULL)
            require('./components/chapter-summary.php');
          else
            require('./components/homepage.php');
        ?>
        <div class='right'></div>
      </div>
    </div>
  </body>
</html>
