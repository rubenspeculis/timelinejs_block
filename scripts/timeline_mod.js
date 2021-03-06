
/**
 * JS file
 */
/* global jQuery:false */
(function ($) {
  "use strict";
  $(document).ready(function() {
    $('.access a').on('click', function(event){
      event.preventDefault();
      $('html, body').animate({
        scrollTop: $('.timelinejs_table').offset().top
        }, 'fast');
    });

    $(document).on('keydown click', 'body', populate_headline);

    $(document).on('LOADED UPDATED', '#storyjs-timeline', function(event){
      var target = event.target;
      if($(target).hasClass('vco-navigation')){
        // This is being used for the purpose of pre-propulating the first
        // instance of the timeline 
        var newHeadline = '<div class="headline"><span class="capitalize">Basin Plan comes into effect</span> - November 2012 </div>';
        $('#timeline_1 .slider-item-container div.slider-item:nth-child(2)').prepend(newHeadline);
        //$('#timeline_1 .content .marker:nth-child(2) .flag').trigger('click');
      }
      $('.time-interval div:nth-child(1)').remove();
      $('.time-interval').prepend('<div style="text-indent: -7px; opacity: 100; left:1727.762557px">2012</div>');
    });
  });

  function populate_headline(){
    $('.slider-item-container').children('div.slider-item').each(function(){
      var date = $(this).find($('h2.date')).html();
      var headline = '<span class="capitalize">' + $(this).find($('h3')).html() + '</span>';
      if(!!date && !!headline){
        var newHeadline = '<div class="headline">'+ headline + ' - ' + date  +'</div>';
        var check = $(this).find($('div.headline'));
        if(!!check){
          $(this).find($('.headline')).remove();
          $(this).prepend(newHeadline);
        }
      }
    });
  }

})(jQuery);

