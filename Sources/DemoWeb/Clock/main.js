window.onload = function() {
 
  const hourHand = document.querySelector('.hourHand');
  const minuteHand = document.querySelector('.minuteHand');
  const secondHand = document.querySelector('.sec');
   
      function setDate() {
          const today = new Date();
           
          const second = today.getSeconds();
          const secondDeg = ((second / 60) * 360) + 360; 
          secondHand.style.transform = `rotate(${secondDeg}deg)`;
           
          const minute = today.getMinutes();
          const minuteDeg = ((minute / 60) * 360); 
          minuteHand.style.transform = `rotate(${minuteDeg}deg)`;
   
          const hour = today.getHours();
          const hourDeg = ((hour / 12 ) * 360 ); 
          hourHand.style.transform = `rotate(${hourDeg}deg)`;
           
      }
      setInterval(setDate, 1000);
    
  }